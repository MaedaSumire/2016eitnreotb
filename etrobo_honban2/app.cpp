/**
 ******************************************************************************
 ** ファイル名 : app.cpp
 **
 ** 概要 : 2輪倒立振子ライントレースロボットのTOPPERS/HRP2用C++サンプルプログラム
 **
 ** 注記 : sample_cpp (ライントレース/尻尾モータ/超音波センサ/リモートスタート)
 ******************************************************************************
 **/

#include "DeviceValueGet.h"
#include "UIGet.h"

#include "CompetitionRunning.h"

#include "CalibrationController.h"

#include "ev3api.h"
#include "app.h"
#include "balancer.h"

#include "DeviceInterface.h"

#include "ExtraStageLookUp.h"
#include "ExtraStageStep.h"

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

BLUET* gpBlueT;

/* 下記のマクロは個体/環境に合わせて変更する必要があります */
#define GYRO_OFFSET           0  /* ジャイロセンサオフセット値(角速度0[deg/sec]時) */
#define TAIL_ANGLE_STAND_UP  93  /* 完全停止時の角度[度] */
#define TAIL_ANGLE_DRIVE      3  /* バランス走行時の角度[度] */
#define CMD_START         '1'    /* リモートスタートコマンド */

/* LCDフォントサイズ */
#define CALIB_FONT (EV3_FONT_SMALL)
#define CALIB_FONT_WIDTH (6/*TODO: magic number*/)
#define CALIB_FONT_HEIGHT (8/*TODO: magic number*/)

// Device objects
// オブジェクトを静的に確保する
DeviceInterface* gDeviceInterface;	// デバイスインターフェイス

// オブジェクトの定義

static UIGet *gUiGet;

static CompetitionRunning *gCompetitionrunning;

static CalibrationController *gCalibrationController;

static ExtraStageLookUp *gExtraStageLookUp;
static ExtraStageStep *gExtraStageStep;

extern int gCourse;

/* メインタスク */
void main_task(intptr_t unused) {

	gDeviceInterface = new DeviceInterface();	// デバイスインターフェイス構築

	/*オブジェクトの生成*/
	gUiGet = new UIGet(gDeviceInterface);
	gpBlueT = gUiGet->GetBlueT();	// ブルーツース構造体の取得

	gCompetitionrunning = new CompetitionRunning(gDeviceInterface, gUiGet);

	gCalibrationController = new CalibrationController(gDeviceInterface, gUiGet);

	gExtraStageLookUp = new ExtraStageLookUp( gDeviceInterface, gUiGet, gCalibrationController );
	gExtraStageStep = new ExtraStageStep(gDeviceInterface, gUiGet, gCalibrationController);

	/* LCD画面表示 */
	ev3_lcd_fill_rect(0, 0, EV3_LCD_WIDTH, EV3_LCD_HEIGHT, EV3_LCD_WHITE);

	/* Open Bluetooth file */
	gpBlueT->pBtFile = ev3_serial_open_file(EV3_SERIAL_BT);
	assert(gpBlueT->pBtFile != NULL);

	/* Bluetooth通信タスクの起動 */
	act_tsk (BT_TASK);

	/*キャリブレーション＆スタート待機*/
	gCalibrationController->Calibrate();

	/* 再度初期化 */
	gDeviceInterface->m_pCLeftMotor->reset();
	gDeviceInterface->m_pCRightMotor->reset();
	gDeviceInterface->m_pCGyroSensor->reset();
	balance_init(); /* 倒立振子API初期化 */

	/**
	 * Main loop for the self-balance control algorithm
	 */

	/*競技走行*/
	gCompetitionrunning->CompetitionRun();

	// Lコース
	if (gCourse == 1) {
		// ルックアップゲート
		gExtraStageLookUp->ExtraRun();
		// ガレージ
	}
	// Rコース
	else if (gCourse == 2) {
		// 階段
		gExtraStageStep->ExtraRun();
		//ガレージ
	}

	/*終了処理*/
	gDeviceInterface->m_pCLeftMotor->reset();
	gDeviceInterface->m_pCRightMotor->reset();
	ter_tsk(BT_TASK);

	//fclose(pbt_File);
	fclose(gpBlueT->pBtFile);

	delete gDeviceInterface;
	delete gUiGet;
	delete gCompetitionrunning;
	delete gCalibrationController;

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

		if (c >= '0') {
			// キーボード押下
			gpBlueT->btcKey = c;
			fputc(gpBlueT->btcKey, gpBlueT->pBtFile); /* エコーバック */
		}

		fputc(c, gpBlueT->pBtFile); /* エコーバック */
	}
}
