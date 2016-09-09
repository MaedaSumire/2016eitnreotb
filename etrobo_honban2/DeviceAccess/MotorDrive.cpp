//モータ駆動
#include "MotorDrive.h"

// コンストラクター
MotorDrive::MotorDrive( DeviceInterface* pDeviceInterface )
{
	m_pDeviceInterface	= pDeviceInterface;
}

//メソッド void 左右モータ値を設定する(左右pwm値)
void MotorDrive::LRMotorDrive(int8_t leftPWM,int8_t rightPWM){
	
	m_pDeviceInterface->m_pCLeftMotor->setPWM(leftPWM);		// 車輪モーター L
	m_pDeviceInterface->m_pCRightMotor->setPWM(rightPWM);	// 車輪モーター R
}

//メソッド void しっぽモータ値を設定する(しっぽ目標角度)
void MotorDrive::TailMotorDrive(float angle){

	float P_GAIN = 2.5;  /* 完全停止用モータ制御比例係数 */
	float PWM_ABS_MAX = 60;  /* 完全停止用モータ制御PWM絶対最大値 */
	float pwm;

	pwm = (float) (angle - m_pDeviceInterface->m_pCTailMotor->getCount()) * P_GAIN; // 比例制御

	/* PWM出力飽和処理 */
	if (pwm > PWM_ABS_MAX){
		pwm = PWM_ABS_MAX;
	}
	else if (pwm < -PWM_ABS_MAX){
		pwm = -PWM_ABS_MAX;
	}

	m_pDeviceInterface->m_pCTailMotor->setPWM(pwm);		// テールモーター

}

// リセット
void MotorDrive::reset()
{
	m_pDeviceInterface->m_pCLeftMotor->reset();
	m_pDeviceInterface->m_pCRightMotor->reset();
	m_pDeviceInterface->m_pCRightMotor->reset();
}
