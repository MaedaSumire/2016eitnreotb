/*
 * DeviceInterface.cpp
 *
 *  Created on: 2016/09/06
 *      Author: 9690333
 */
#include "DeviceInterface.h"


/////////////////////
//	CDeviceInterface
/////////////////////
DeviceInterface::DeviceInterface()	// コンストラクター
{
	m_pCTouchSensor	= new CwrTouchSensor(PORT_1);	// タッチセンサー
	m_pCSonarSensor	= new CwrSonarSensor(PORT_2);	// ソナーセンサー
	m_pCColorSensor	= new CwrColorSensor(PORT_3);	// カラーセンサー
	m_pCGyroSensor	= new CwrGyroSensor (PORT_4);	// ジャイロセンサー
	m_pCLeftMotor	= new CwrWheelMotor (PORT_C);	// 車輪モーター L
	m_pCRightMotor	= new CwrWheelMotor (PORT_B);	// 車輪モーター R
	m_pCTailMotor	= new CwrTailMotor  (PORT_A);	// テールモーター
	m_pCClock		= new CwrClock();				// クロック

	m_pCBattery		= new CwrBattery();			// バッテリー
	m_pCLEDLight	= new CwrLEDLight();		// LED
	m_pCSpeaker		= new CwrSpeaker();			// スピーカー
}

DeviceInterface::~DeviceInterface()	// デストラクター
{
	delete	m_pCTouchSensor;	// タッチセンサー
	delete	m_pCSonarSensor;	// ソナーセンサー
	delete	m_pCColorSensor;	// カラーセンサー
	delete	m_pCGyroSensor;		// ジャイロセンサー
	delete	m_pCLeftMotor;		// 車輪モーター L
	delete	m_pCRightMotor;		// 車輪モーター R
	delete	m_pCTailMotor;		// テールモーター
	delete	m_pCClock;			// クロック

	delete	m_pCBattery;		// バッテリー
	delete	m_pCLEDLight;		// LED
	delete	m_pCSpeaker;		// スピーカー
}


///////////////////////////////////////////////////
//	CwrTouchSensor		タッチセンサー
///////////////////////////////////////////////////
CwrTouchSensor::CwrTouchSensor( ePortS port ) : // コンストラクター
	TouchSensor( port )
{
}
CwrTouchSensor::~CwrTouchSensor()	// デストラクター
{
}

///////////////////////////////////////////////////
//	CwrSonarSensor		ソナーセンサー
///////////////////////////////////////////////////
CwrSonarSensor::CwrSonarSensor( ePortS port ) :	// コンストラクター
	SonarSensor( port )
{
}
CwrSonarSensor::~CwrSonarSensor()	// デストラクター
{
}

///////////////////////////////////////////////////
//	CwrColorSensor		カラーセンサー
///////////////////////////////////////////////////
CwrColorSensor::CwrColorSensor( ePortS port ) :	// コンストラクター
	ColorSensor( port )
{
}
CwrColorSensor::~CwrColorSensor()	// デストラクター
{
}

///////////////////////////////////////////////////
//	CwrGyroSensor		ジャイロセンサー
///////////////////////////////////////////////////
CwrGyroSensor::CwrGyroSensor( ePortS port ) :	// コンストラクター
	GyroSensor( port )
{
}
CwrGyroSensor::~CwrGyroSensor()	// デストラクター
{
}

///////////////////////////////////////////////////
//	CwrMotor		モーター
///////////////////////////////////////////////////
CwrMotor::CwrMotor( ePortM port ) :	// コンストラクター
	Motor( port )
{
}
CwrMotor::~CwrMotor()	// デストラクター
{
}

///////////////////////////////////////////////////
//	CwrWheelMotor		車輪モーター
///////////////////////////////////////////////////
CwrWheelMotor::CwrWheelMotor( ePortM port ) : CwrMotor( port )	// コンストラクター
{
}
CwrWheelMotor::~CwrWheelMotor()	// デストラクター
{
}

///////////////////////////////////////////////////
//	CwrTailMotor		テールモーター
///////////////////////////////////////////////////
CwrTailMotor::CwrTailMotor( ePortM port ) : CwrMotor( port )	// コンストラクター
{
}
CwrTailMotor::~CwrTailMotor()	// デストラクター
{
}

///////////////////////////////////////////////////
//	CwrClock		クロック
///////////////////////////////////////////////////
CwrClock::CwrClock() : Clock()	// コンストラクター
{
}
CwrClock::~CwrClock()	// デストラクター
{
}

///////////////////////////////////////////////////
//	CwrBattery		バッテリー
///////////////////////////////////////////////////
CwrBattery::CwrBattery()	// コンストラクター
{
}
CwrBattery::~CwrBattery()	// デストラクター
{
}
int	CwrBattery::GetmA()	// バッテリの電流を取得する．（mA）
{
	return	ev3_battery_current_mA();
}
int	CwrBattery::GetmV()	// バッテリの電圧を取得する．（mV）
{
	return	ev3_battery_voltage_mV();
}

///////////////////////////////////////////
//	CwrLEDLight	LED
///////////////////////////////////////////
CwrLEDLight::CwrLEDLight()	// コンストラクター
{
}
CwrLEDLight::~CwrLEDLight()	// デストラクター
{
}
ER	CwrLEDLight::SetColor( ledcolor_t	color )	// LEDライトのカラーを設定する
{
	return	ev3_led_set_color (color);
}

///////////////////////////////////////////
//	CwrSpeaker	スピーカー
///////////////////////////////////////////
CwrSpeaker::CwrSpeaker()	// コンストラクター
{
}
CwrSpeaker::~CwrSpeaker()	// デストラクター
{
}

ER 	CwrSpeaker::SetVolume(uint8_t nVolume)	// 音量を調整する．
{
	return	ev3_speaker_set_volume(nVolume);
}
ER 	CwrSpeaker::PlayTone(					// 指定した周波数でトーン出力する．今再生しているサウンドは停止される
					uint16_t nFrequency,	// トーンの周波数
					int32_t nDuration		// 出力持続時間．単位：ミリ秒．SOUND_MANUAL_STOPを指定した場合は手動で停止する．
					)
{
	return	ev3_speaker_play_tone( nFrequency,nDuration );
}
ER 	CwrSpeaker::PlayFile(					// 指定したWAVファイル（8-bit 8kHz mono）を再生する．
					const memfile_t *p_memfile,	// WAVファイルのメモリファイルへのポインタ
					int32_t nDuration			// 出力持続時間．単位：ミリ秒．SOUND_MANUAL_STOPを指定した場合は手動で停止しないと最後まで再生する．
					)
{
	return	ev3_speaker_play_file( p_memfile, nDuration );
}
ER 	CwrSpeaker::Stop()						// 今再生しているサウンドを停止する． [詳解]
{
	return	ev3_speaker_stop();
}



