/**
 ******************************************************************************
 ** ファイル名 : app.cpp
 **
 ** 概要 : 2輪倒立振子ライントレースロボットのTOPPERS/HRP2用C++サンプルプログラム
 **
 ** 注記 : sample_cpp (ライントレース/尻尾モータ/超音波センサ/リモートスタート)
 ******************************************************************************
 **/

#include "ev3api.h"
#include "app.h"
#include "balancer.h"
#include "TouchSensor.h"
#include "SonarSensor.h"
#include "ColorSensor.h"
#include "GyroSensor.h"
#include "Motor.h"
#include "Clock.h"

using namespace ev3api;

#define DEBUG

#ifdef DEBUG
#define _debug(x) (x)
#else
#define _debug(x)
#endif

/* Bluetooth */
static int32_t bt_cmd = 0; /* Bluetoothコマンド 1:リモートスタート */
static FILE *bt = NULL; /* Bluetoothファイルハンドル */

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


static double tail_angle_stand_up = 93;/* 完全停止時の角度[度] (2016/06/24_変更)*/

/* LCDフォントサイズ */
#define CALIB_FONT (EV3_FONT_SMALL)
#define CALIB_FONT_WIDTH (6/*TODO: magic number*/)
#define CALIB_FONT_HEIGHT (8/*TODO: magic number*/)

//PID制御用
#define DELTA_T	0.004
#define KP	1.4
#define KI	0.2
#define KD	0.02

static double	diff[2];
static double	integral;
double p, i, d;
int32_t nBri;

/* 関数プロトタイプ宣言 */
static int32_t sonar_alert(void);
static void tail_control(int32_t angle);


typedef struct{
	int brightness;
	int turningValue;
} SDD ;
SDD SectionDecisionDataGet(int now_section);


/* オブジェクトへのポインタ定義 */
TouchSensor* touchSensor;
SonarSensor* sonarSensor;
ColorSensor* colorSensor;
GyroSensor* gyroSensor;
Motor* leftMotor;
Motor* rightMotor;
Motor* tailMotor;
Clock* clock;

//グローバル変数
int32_t g_motor_ang_l, g_motor_ang_r, g_gyro, g_volt;
uint8_t g_unAmbient, g_unBrightness;

/* メインタスク */
void main_task(intptr_t unused) {
	int8_t forward; /* 前後進命令 */
	int8_t turn; /* 旋回命令 */
	int8_t pwm_L, pwm_R; /* 左右モータPWM出力 */

	/* 各オブジェクトを生成・初期化する */
	touchSensor = new TouchSensor(PORT_1);
	sonarSensor = new SonarSensor(PORT_2);
	colorSensor = new ColorSensor(PORT_3);
	gyroSensor = new GyroSensor(PORT_4);
	leftMotor = new Motor(PORT_C);
	rightMotor = new Motor(PORT_B);
	tailMotor = new Motor(PORT_A);
	clock = new Clock();
	
	SDD nowSDD2;

	/* LCD画面表示 */
	ev3_lcd_fill_rect(0, 0, EV3_LCD_WIDTH, EV3_LCD_HEIGHT, EV3_LCD_WHITE);
	ev3_lcd_draw_string("EV3way-ET sample_cpp", 0, CALIB_FONT_HEIGHT * 1);

	/* 尻尾モーターのリセット */
	tailMotor->reset();

	/* Open Bluetooth file */
	bt = ev3_serial_open_file(EV3_SERIAL_BT);
	assert(bt != NULL);

	/* Bluetooth通信タスクの起動 */
	act_tsk (BT_TASK);
	
	ev3_led_set_color(LED_ORANGE); /* 初期化完了通知 */
	
	char cBuff[1024];
	sprintf(cBuff, "PID制御(turn)_P:0.4 I:1.0 D:0.0\n ,クロック,P制御turn,センサ値輝度,モータ\n");
	fputs(cBuff, bt); // エコーバック

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

		if (touchSensor->isPressed()) {
			break; /* タッチセンサが押された */
		}
		g_unBrightness  = colorSensor->getBrightness();

		clock->sleep(10);
	}

	/* 走行モーターエンコーダーリセット */
	leftMotor->reset();
	rightMotor->reset();

	/* ジャイロセンサーリセット */
	gyroSensor->reset();
	balance_init(); /* 倒立振子API初期化 */

	ev3_led_set_color(LED_GREEN); /* スタート通知 */

	/**
	 * Main loop for the self-balance control algorithm
	 */
	
	uint32_t unStartTime	= clock->now();
	
	while (1) {
		if (ev3_button_is_pressed(BACK_BUTTON))
			break;

		tail_control(TAIL_ANGLE_DRIVE); /* バランス走行用角度に制御 */

		if (sonar_alert() == 1) /* 障害物検知 */
		{
			forward = turn = 0; /* 障害物を検知したら停止 */
		} else {
			forward = 40; /* 前進命令 */
			g_unBrightness  = colorSensor->getBrightness();
			nBri = 26;
			
			if( clock->now() - unStartTime > 1000){
				
				
				
        		//PID
        		diff[0] = diff[1];
        		diff[1] = nBri - g_unBrightness;
        		integral += (diff[1] + diff[0]) / 2.0 * DELTA_T;
				
				p = KP * diff[1];
				i = KI * integral;
				d = KD * (diff[1] - diff[0]) / DELTA_T;
				
        		turn = p+ i + d;
			
				if(turn < -100 ){
					turn = -100;
				}else if (turn > 100){
					turn = 100;
				}
				
				nowSDD2 = SectionDecisionDataGet(1);
				
			}
			
		}

		/* 倒立振子制御API に渡すパラメータを取得する */
		g_motor_ang_l = leftMotor->getCount();
		g_motor_ang_r = rightMotor->getCount();
		g_gyro = gyroSensor->getAnglerVelocity();
		g_volt = ev3_battery_voltage_mV();

		/* 倒立振子制御APIを呼び出し、倒立走行するための */
		/* 左右モータ出力値を得る */
		balance_control((float) forward, (float) turn, (float) g_gyro,
				(float) GYRO_OFFSET, (float) g_motor_ang_l,
				(float) g_motor_ang_r, (float) g_volt, (int8_t *) &pwm_L,
				(int8_t *) &pwm_R);

		leftMotor->setPWM(pwm_L);
		rightMotor->setPWM(pwm_R);

		// ログ
		char cBuff[1024];
		sprintf(cBuff, "Main,%d,%d,%d,%d, %d, %d\n", clock->now(), turn,g_unBrightness,g_motor_ang_l, g_motor_ang_r, g_gyro);
		fputs(cBuff, bt); // エコーバック

		clock->sleep(3); /* 4msec周期起動 */
	}
	leftMotor->reset();
	rightMotor->reset();

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
		distance = sonarSensor->getDistance();
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
	float pwm = (float) (angle - tailMotor->getCount()) * P_GAIN; /* 比例制御 */
	/* PWM出力飽和処理 */
	if (pwm > PWM_ABS_MAX) {
		pwm = PWM_ABS_MAX;
	} else if (pwm < -PWM_ABS_MAX) {
		pwm = -PWM_ABS_MAX;
	}

	tailMotor->setPWM(pwm);
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


//****************************************
//区間データ群を返却する関数
//
//使い方はmethod.txtを参照。
//****************************************
SDD SectionDecisionDataGet(int now_section){

	int Data_brightness[8] = {0,1,2,3,4,5,6,7};
	int Data_turningValue[8] = {0,1,2,3,4,5,6,7};
	SDD nowSDD;
	
	
	nowSDD.brightness = Data_brightness[now_section];
	nowSDD.turningValue = Data_turningValue[now_section];

	return nowSDD;
};