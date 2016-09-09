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
#include "UIGet.h"

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

#include "CalibrationController.h"
#include "StartController.h"

#include "ExtraStageLookUp.h"
#include "ExtraStageStep.h"

#include "ev3api.h"
#include "app.h"
#include "balancer.h"
#include "TouchSensor.h"
#include "SonarSensor.h"
#include "ColorSensor.h"
#include "GyroSensor.h"
#include "Motor.h"
#include "Clock.h"


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


BLUET*	gpBlueT;


/* 下記のマクロは個体/環境に合わせて変更する必要があります */
#define GYRO_OFFSET           0  /* ジャイロセンサオフセット値(角速度0[deg/sec]時) */
#define LIGHT_WHITE          40  /* 白色の光センサ値 */
#define LIGHT_BLACK           0  /* 黒色の光センサ値 */
#define TAIL_ANGLE_STAND_UP  93  /* 完全停止時の角度[度] */
#define TAIL_ANGLE_DRIVE      3  /* バランス走行時の角度[度] */
#define CMD_START         '1'    /* リモートスタートコマンド */

/* LCDフォントサイズ */
#define CALIB_FONT (EV3_FONT_SMALL)
#define CALIB_FONT_WIDTH (6/*TODO: magic number*/)
#define CALIB_FONT_HEIGHT (8/*TODO: magic number*/)


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
static UIGet *gUiGet;

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

static CalibrationController *gCalibrationController;
static StartController *gStartController;

static ExtraStageLookUp *gExtraStageLookUp;
static ExtraStageStep *gExtraStageStep;


/* メインタスク */
void main_task(intptr_t unused) {

	/*オブジェクトの生成*/
	gMotorDrive = new MotorDrive(gLeftMotor, gRightMotor, gTailMotor);
	gDeviceValueGet = new DeviceValueGet(gSonarSensor, gColorSensor, gGyroSensor, gLeftMotor, gRightMotor, gTailMotor);
	gUiGet = new UIGet(gTouchSensor);
	gpBlueT	= gUiGet->GetBlueT();	// ブルーツース構造体の取得

	gRunningdata = new RunningData();
	gPidcalculation = new PIDCalculation();
	gRunningdataget = new RunningDataGet(gRunningdata);
	gRunningcalculation = new RunningCalculation(gPidcalculation, gRunningdataget);
	gRunningcontroller = new RunningController(gDeviceValueGet, gRunningcalculation, gMotorDrive, gUiGet, gClock);

	gSectiondecisiondata = new SectionDecisionData();
	gSectiondecisiondataget = new SectionDecisionDataGet(gSectiondecisiondata);
	gSectiondecision = new SectionDecision(gSectiondecisiondataget);
	gSectiondecisioncontroller = new SectionDecisionController(gSectiondecision, gDeviceValueGet);

	gCompetitionrunning = new CompetitionRunning(gRunningcontroller, gSectiondecisioncontroller, gMotorDrive, gUiGet, gClock);

	gCalibrationController = new CalibrationController(gGyroSensor, gClock, gMotorDrive, gDeviceValueGet, gUiGet);
	gStartController = new StartController(gCalibrationController, gMotorDrive, gUiGet, gClock);

	gExtraStageLookUp = new ExtraStageLookUp(gMotorDrive, gDeviceValueGet, gClock);
	gExtraStageStep = new ExtraStageStep(gMotorDrive, gDeviceValueGet, gPidcalculation, gRunningcalculation, gClock);


	/* LCD画面表示 */
	ev3_lcd_fill_rect(0, 0, EV3_LCD_WIDTH, EV3_LCD_HEIGHT, EV3_LCD_WHITE);

	gpBlueT->pBtFile	= ev3_serial_open_file(EV3_SERIAL_BT);
	assert(gpBlueT->pBtFile != NULL);

	/* Bluetooth通信タスクの起動 */
	act_tsk (BT_TASK);

	/*キャリブレーション*/
	gCalibrationController->Calibrate();

	/* スタート待機 */
	gStartController->StartDicision();

	/* 再度初期化 */
	gLeftMotor.reset();
	gRightMotor.reset();
	gGyroSensor.reset();
	balance_init(); /* 倒立振子API初期化 */

	/**
	 * Main loop for the self-balance control algorithm
	 */
	
	/*競技走行*/
	//gCompetitionrunning-> CompetitionRun();

	/*ルックアップゲート攻略*/
	//gExtraStageLookUp->ExtraRun();

	/*階段攻略*/
	gExtraStageStep->ExtraRun();
	
	/*終了処理*/
	gLeftMotor.reset();
	gRightMotor.reset();
	ter_tsk(BT_TASK);

	fclose(gpBlueT->pBtFile);

	ext_tsk();

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
		uint8_t c = fgetc(gpBlueT->pBtFile);	// 受信

		if( c >= '0' ){
			// キーボード押下
			gpBlueT->btcKey	= c;
			fputc(gpBlueT->btcKey, gpBlueT->pBtFile); /* エコーバック */
		}

		fputc(c, gpBlueT->pBtFile); /* エコーバック */
	}
}
