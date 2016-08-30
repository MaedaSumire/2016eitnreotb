/**
 ******************************************************************************
 ** ファイル名 : app.cpp
 **
 ** 概要 : 2輪倒立振子ライントレースロボットのTOPPERS/HRP2用C++サンプルプログラム
 **
 ** 注記 : sample_cpp (ライントレース/尻尾モータ/超音波センサ/リモートスタート)
 ******************************************************************************
 **/

#include "MotorDrive.h"
#include "DeviceValueGet.h"

#include "RunningData.h"
#include "PIDCalculation.h"
#include "RunningDataGet.h"
#include "RunningCalculation.h"
#include "RunningController.h"

#include "SectionDecisionData.h"
#include "SectionDecisionDataGet.h"
#include "SectionDecision.h"
#include "SectionDecisionController.h"

#include "CompetitionRunning.h"

#include "ev3api.h"
#include "app.h"
#include "balancer.h"
#include "TouchSensor.h"
#include "SonarSensor.h"
#include "ColorSensor.h"
#include "GyroSensor.h"
#include "Motor.h"
#include "Clock.h"



//using namespace ev3api;

using ev3api::ColorSensor;
using ev3api::SonarSensor;
using ev3api::GyroSensor;
using ev3api::TouchSensor;
using ev3api::Motor;
using ev3api::Clock;

#define DEBUG

#ifdef DEBUG
#define _debug(x) (x)
#else
#define _debug(x)
#endif

/* Bluetooth */
static int32_t bt_cmd = 0; /* Bluetoothコマンド 1:リモートスタート */
static FILE *bt = NULL; /* Bluetoothファイルハンドル */
static double tail_angle_stand_up = 93;/* 完全停止時の角度[度] (2016/06/24_変更)*/

/* 下記のマクロは個体/環境に合わせて変更する必要があります */
#define GYRO_OFFSET           0  /* ジャイロセンサオフセット値(角速度0[deg/sec]時) */
#define LIGHT_WHITE          40  /* 白色の光センサ値 */
#define LIGHT_BLACK           0  /* 黒色の光センサ値 */
#define SONAR_ALERT_DISTANCE 30  /* 超音波センサによる障害物検知距離[cm] */
#define TAIL_ANGLE_STAND_UP  93  /* 完全停止時の角度[度] */
#define TAIL_ANGLE_DRIVE      3  /* バランス走行時の角度[度] */
#define P_GAIN             2.5F  /* 完全停止用モータ制御比例係数 */
#define PWM_ABS_MAX          60  /* 完全停止用モータ制御PWM絶対最大値 */
//#define DEVICE_NAME     "ET0"  /* Bluetooth名 hrp2/target/ev3.h BLUETOOTH_LOCAL_NAMEで設定 */
//#define PASS_KEY        "1234" /* パスキー    hrp2/target/ev3.h BLUETOOTH_PIN_CODEで設定 */
#define CMD_START         '1'    /* リモートスタートコマンド */

/* LCDフォントサイズ */
#define CALIB_FONT (EV3_FONT_SMALL)
#define CALIB_FONT_WIDTH (6/*TODO: magic number*/)
#define CALIB_FONT_HEIGHT (8/*TODO: magic number*/)

/* 関数プロトタイプ宣言 */
static int32_t sonar_alert(void);
static void tail_control(int32_t angle);

// Device objects
// オブジェクトを静的に確保する
TouchSensor gTouchSensor(PORT_1);
SonarSensor gSonarSensor(PORT_2);
ColorSensor gColorSensor(PORT_3);
GyroSensor gGyroSensor(PORT_4);
Motor gLeftMotor(PORT_C);
Motor gRightMotor(PORT_B);
Motor gTailMotor(PORT_A);
Clock gClock;

// オブジェクトの定義
static MotorDrive *gMotorDrive;
static DeviceValueGet *gDeviceValueGet;
static PIDCalculation *gPidcalculation;

static RunningData *gRunningdata;
static RunningDataGet *gRunningdataget;
static RunningCalculation *gRunningcalculation;
static RunningController *gRunningcontroller;

static SectionDecisionData *gSectiondecisiondata;
static SectionDecisionDataGet *gSectiondecisiondataget;
static SectionDecision *gSectiondecision;
static SectionDecisionController *gSectiondecisioncontroller;

static CompetitionRunning *gCompetitionrunning;

//グローバル変数
int32_t g_motor_ang_l, g_motor_ang_r, g_gyro, g_volt;
uint8_t g_unAmbient, g_unBrightness;

/* メインタスク */
void main_task(intptr_t unused) {
	gMotorDrive = new MotorDrive(gLeftMotor, gRightMotor, gTailMotor);
	gDeviceValueGet = new DeviceValueGet(gTouchSensor, gSonarSensor, gColorSensor, gGyroSensor, gLeftMotor, gRightMotor, gTailMotor);

	gRunningdata = new RunningData();
	gPidcalculation = new PIDCalculation();
	gRunningdataget = new RunningDataGet(gRunningdata);
	gRunningcalculation = new RunningCalculation(gRunningdataget,gPidcalculation);
	gRunningcontroller = new RunningController(gDeviceValueGet,gRunningcalculation,gMotorDrive);

	gSectiondecisiondata = new SectionDecisionData();
	gSectiondecisiondataget = new SectionDecisionDataGet(gSectiondecisiondata);
	gSectiondecision = new SectionDecision(gSectiondecisiondataget);
	gSectiondecisioncontroller = new SectionDecisionController(gSectiondecision, gDeviceValueGet);

	gCompetitionrunning = new CompetitionRunning(gRunningcontroller, gSectiondecisioncontroller);

	/* LCD画面表示 */
	ev3_lcd_fill_rect(0, 0, EV3_LCD_WIDTH, EV3_LCD_HEIGHT, EV3_LCD_WHITE);
	ev3_lcd_draw_string("EV3way-ET sample_cpp", 0, CALIB_FONT_HEIGHT * 1);

	/* 尻尾モーターのリセット */
	gTailMotor.reset();

	/* Open Bluetooth file */
	bt = ev3_serial_open_file(EV3_SERIAL_BT);
	assert(bt != NULL);

	/* Bluetooth通信タスクの起動 */
	act_tsk (BT_TASK);
	
	ev3_led_set_color(LED_ORANGE); /* 初期化完了通知 */
	
//	char cBuff[1024];
//	sprintf(cBuff, "PID制御(turn)_P:0.4 I:1.0 D:0.0\n ,クロック,P制御turn,センサ値輝度,モータ\n");
//	fputs(cBuff, bt); // エコーバック

	/* スタート待機 */
	while (1) {
		tail_control(tail_angle_stand_up); /* 完全停止用角度に制御 */

		//調整機能を導入
		if (ev3_button_is_pressed(UP_BUTTON))/* 尻尾の角度調整 */
		{
			tail_angle_stand_up = tail_angle_stand_up + 0.1;
		}

		if (ev3_button_is_pressed(DOWN_BUTTON))/* 尻尾の角度調整 */
		{
			tail_angle_stand_up = tail_angle_stand_up - 0.1;
		}
		//ここまで

		if (bt_cmd == 1) {
			break; /* リモートスタート */
		}

		if ((gDeviceValueGet->DeviceValueGetter()).touch) {
			break; /* タッチセンサが押された */
		}
		g_unBrightness  = gColorSensor.getBrightness();

		gClock.sleep(10);
	}

	/* 走行モーターエンコーダーリセット */
	gLeftMotor.reset();
	gRightMotor.reset();

	/* ジャイロセンサーリセット */
	gGyroSensor.reset();
	balance_init(); /* 倒立振子API初期化 */

	ev3_led_set_color(LED_GREEN); /* スタート通知 */

	/**
	 * Main loop for the self-balance control algorithm
	 */
	
	uint32_t unStartTime	= gClock.now();
	
	while (1) {
		if (ev3_button_is_pressed(BACK_BUTTON))
			break;

		tail_control(TAIL_ANGLE_DRIVE); /*a バランス走行用角度に制御 */


		g_unBrightness  = gColorSensor.getBrightness();
		//nBri = 26;


//		if (sonar_alert() == 1) /* 障害物検知 */
//		{
//			forward = turn = 0; /* 障害物を検知したら停止 */
//		}


		gCompetitionrunning-> CompetitionRun();

		// ログ
//		char cBuff[1024];
//		sprintf(cBuff, "Main,%d\n", gClock.now());
//		fputs(cBuff, bt); // エコーバック



		gClock.sleep(3); /* 4msec周期起動 */
	}
	gLeftMotor.reset();
	gRightMotor.reset();

	ter_tsk(BT_TASK);
	fclose(bt);

	ext_tsk();
}

//*****************************************************************************
// 関数名 : sonar_alert
// 引数 : 無し
// 返り値 : 1(障害物あり)/0(障害物無し)
// 概要 : 超音波センサによる障害物検知
//*****************************************************************************
static int32_t sonar_alert(void) {
	static uint32_t counter = 0;
	static int32_t alert = 0;

	int32_t distance;

	if (++counter == 40 / 4) /* 約40msec周期毎に障害物検知  */
	{
		/*
		 * 超音波センサによる距離測定周期は、超音波の減衰特性に依存します。
		 * NXTの場合は、40msec周期程度が経験上の最短測定周期です。
		 * EV3の場合は、要確認
		 */
		distance = gSonarSensor.getDistance();
		if ((distance <= SONAR_ALERT_DISTANCE) && (distance >= 0)) {
			alert = 1; /* 障害物を検知 */
		} else {
			alert = 0; /* 障害物無し */
		}
		counter = 0;
	}

	return alert;
}

//*****************************************************************************
// 関数名 : tail_control
// 引数 : angle (モータ目標角度[度])
// 返り値 : 無し
// 概要 : 走行体完全停止用モータの角度制御
//*****************************************************************************
static void tail_control(int32_t angle) {
	float pwm = (float) (angle - gTailMotor.getCount()) * P_GAIN; /* 比例制御 */
	/* PWM出力飽和処理 */
	if (pwm > PWM_ABS_MAX) {
		pwm = PWM_ABS_MAX;
	} else if (pwm < -PWM_ABS_MAX) {
		pwm = -PWM_ABS_MAX;
	}

	gTailMotor.setPWM(pwm);
}

//*****************************************************************************
// 関数名 : bt_task
// 引数 : unused
// 返り値 : なし
// 概要 : Bluetooth通信によるリモートスタート。 Tera Termなどのターミナルソフトから、
//       ASCIIコードで1を送信すると、リモートスタートする。
//*****************************************************************************
void bt_task(intptr_t unused) {

	while (1) {
		uint8_t c = fgetc(bt); /* 受信 */
		switch (c) {
		case '1':
			bt_cmd = 1;
			break;
		default:
			break;
		}
		fputc(c, bt); /* エコーバック */
	}
}
