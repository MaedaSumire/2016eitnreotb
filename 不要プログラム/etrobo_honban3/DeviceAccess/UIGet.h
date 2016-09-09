#ifndef EV3_APP_UIGET_H_
#define EV3_APP_UIGET_H_

#include "ev3api.h"
#include "TouchSensor.h"

//Button -- Left, Right, Up, Down, Back, Enter, None
//btc -- bluetoothcommand (key)
//touvh -- TouchSensorisPressed TF
typedef struct{
	char Button;	// EV3 本体ボタン
	uint8_t btcKey;	// ブルーツース通信機器　キーボード入力
	bool touch;		// EV3タッチセンサー
} UI ;

typedef struct{		// ブルーツース構造体
	uint8_t btcKey;	// ブルーツース通信機器　キーボード入力
	FILE* pBtFile;	// ブルーツースFILEポインター
	char* pcLogBuff;	// ログ出力用文字列バッファーポインター(使用毎にメモリー確保すると時間が掛かる為、ここに確保した)
} BLUET ;

class UIGet {
public:
	UIGet(ev3api::TouchSensor& touchsensor);	// コンストラクター

	UI UIGetter();

	BLUET*	GetBlueT();	// ブルーツースインスタンス取得

	void	WriteLog(char* cBuff);	// ブルーツースログ出力

private:
	ev3api::TouchSensor& mTouchSensor;	// タッチセンサーインスタンス

	char	mLogBuff[256];	// ログ出力用文字列バッファー
	BLUET	mBlueT;		// ブルーツースインスタンス
};

#endif  // EV3_APP_UIGET_H_
