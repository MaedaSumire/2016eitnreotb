//モータ駆動
#include "MotorDrive.h"

MotorDrive::MotorDrive(ev3api::Motor& leftmotor,
		ev3api::Motor& rightmotor,
		ev3api::Motor& tailmotor)
		:mLeftMotor(leftmotor),
		 mRightMotor(rightmotor),
		 mTailMotor(tailmotor){
}

//メソッド void 左右モータ値を設定する(左右pwm値)
void MotorDrive::LRMotorDrive(int8_t leftPWM,int8_t rightPWM){
	mLeftMotor.setPWM(leftPWM);
	mRightMotor.setPWM(rightPWM);
}

//メソッド void しっぽモータ値を設定する(しっぽ目標角度)
void MotorDrive::TailMotorDrive(float angle){

	float P_GAIN = 2.5;  /* 完全停止用モータ制御比例係数 */
	float PWM_ABS_MAX = 60;  /* 完全停止用モータ制御PWM絶対最大値 */
	float pwm;

	pwm = (float) (angle - mTailMotor.getCount()) * P_GAIN; /* 比例制御 */
	/* PWM出力飽和処理 */
	if (pwm > PWM_ABS_MAX){
		pwm = PWM_ABS_MAX;
	}
	else if (pwm < -PWM_ABS_MAX){
		pwm = -PWM_ABS_MAX;
	}

	mTailMotor.setPWM(pwm);

}
