////////////////////////////////////////////////
// デバイスインターフェイス定義
////////////////////////////////////////////////
#ifndef DEVICE_INTERFACE_H_
#define DEVICE_INTERFACE_H_

#include "ev3api.h"
#include "TouchSensor.h"
#include "SonarSensor.h"
#include "ColorSensor.h"
#include "GyroSensor.h"
#include "Motor.h"
#include "Clock.h"

///////////////////////////////////////////
//	CwrTouchSensor	タッチセンサー ラッパークラス
///////////////////////////////////////////
class	CwrTouchSensor : public ev3api::TouchSensor{
public:
	CwrTouchSensor( ePortS port );		// コンストラクター
	~CwrTouchSensor();	// デストタクター
};

///////////////////////////////////////////
//	CwrSonarSensor	ソナーセンサー ラッパークラス
///////////////////////////////////////////
class	CwrSonarSensor : public ev3api::SonarSensor{
public:
	CwrSonarSensor( ePortS port );		// コンストラクター
	~CwrSonarSensor();	// デストタクター
};

///////////////////////////////////////////
//	CwrColorSensor	カラーセンサー ラッパークラス
///////////////////////////////////////////
class	CwrColorSensor : public ev3api::ColorSensor{
public:
	CwrColorSensor( ePortS port );		// コンストラクター
	~CwrColorSensor();	// デストタクター
};

///////////////////////////////////////////
//	CwrGyroSensor	ジャイロセンサー ラッパークラス
///////////////////////////////////////////
class	CwrGyroSensor : public ev3api::GyroSensor{
public:
	CwrGyroSensor( ePortS port );		// コンストラクター
	~CwrGyroSensor();	// デストタクター
};

///////////////////////////////////////////
//	CwrMotor	モーター ラッパークラス
///////////////////////////////////////////
class	CwrMotor : public ev3api::Motor{
public:
	CwrMotor( ePortM port );		// コンストラクター
	~CwrMotor();		// デストタクター
};

///////////////////////////////////////////
//	CwrWheelMotor	車輪モータークラス
///////////////////////////////////////////
class	CwrWheelMotor : public CwrMotor{
public:
	CwrWheelMotor( ePortM port );		// コンストラクター
	~CwrWheelMotor();		// デストタクター
};

///////////////////////////////////////////
//	CwrTailMotor	テールモータークラス
///////////////////////////////////////////
class	CwrTailMotor : public CwrMotor{
public:
	CwrTailMotor( ePortM port );		// コンストラクター
	~CwrTailMotor();	// デストタクター
};

///////////////////////////////////////////
//	CwrClock	クロッククラス
///////////////////////////////////////////
class	CwrClock : public ev3api::Clock{
public:
	CwrClock();		// コンストラクター
	~CwrClock();	// デストタクター
};

///////////////////////////////////////////
//	CwrBattery	バッテリークラス
///////////////////////////////////////////
class	CwrBattery{
public:
	CwrBattery();		// コンストラクター
	~CwrBattery();	// デストタクター

public:
	int	GetmA();	// バッテリの電流を取得する．（mA）
	int	GetmV();	// バッテリの電圧を取得する．（mV）
};

///////////////////////////////////////////
//	CwrLEDLight	LEDクラス
///////////////////////////////////////////
class	CwrLEDLight{
public:
	CwrLEDLight();		// コンストラクター
	~CwrLEDLight();	// デストタクター

public:
	ER	SetColor( ledcolor_t	color );	// LEDライトのカラーを設定する
};

///////////////////////////////////////////
//	CwrSpeaker	スピーカークラス
///////////////////////////////////////////
class	CwrSpeaker{
public:
	CwrSpeaker();		// コンストラクター
	~CwrSpeaker();	// デストタクター

public:
	ER 	SetVolume(uint8_t nVolume);	// 音量を調整する．
	ER 	PlayTone(					// 指定した周波数でトーン出力する．今再生しているサウンドは停止される
					uint16_t nFrequency,	// トーンの周波数
					int32_t nDuration		// 出力持続時間．単位：ミリ秒．SOUND_MANUAL_STOPを指定した場合は手動で停止する．
					);
	ER 	PlayFile(					// 指定したWAVファイル（8-bit 8kHz mono）を再生する．
					const memfile_t *p_memfile,	// WAVファイルのメモリファイルへのポインタ
					int32_t nDuration			// 出力持続時間．単位：ミリ秒．SOUND_MANUAL_STOPを指定した場合は手動で停止しないと最後まで再生する．
					);
	ER 	Stop();						// 今再生しているサウンドを停止する． [詳解]
};

///////////////////////////////////////////
//	CDeviceInterface	デバイスインターフェイスクラス
///////////////////////////////////////////
class	CDeviceInterface{
public:
	CDeviceInterface();		// コンストラクター
	~CDeviceInterface();	// デストタクター

public:
	CwrTouchSensor*	m_pCTouchSensor;	// タッチセンサー
	CwrSonarSensor*	m_pCSonarSensor;	// ソナーセンサー
	CwrColorSensor*	m_pCColorSensor;	// カラーセンサー
	CwrGyroSensor*	m_pCGyroSensor;		// ジャイロセンサー
	CwrWheelMotor*	m_pCLeftMotor;		// 車輪モーター L
	CwrWheelMotor*	m_pCRightMotor;		// 車輪モーター R
	CwrTailMotor*	m_pCTailMotor;		// テールモーター
	CwrClock*		m_pCClock;			// クロック

	CwrBattery*		m_pCBattery;		// バッテリークラス
	CwrLEDLight*	m_pCLEDLight;		// LEDクラス
	CwrSpeaker*		m_pCSpeaker;		// スピーカークラス
};
#endif  // DEVICE_INTERFACE_H_
