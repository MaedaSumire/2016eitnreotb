//モータ駆動
#include "MotorDrive.h"

MotorDrive::MotorDrive(ev3api::Motor& leftMotor,
		ev3api::Motor& rightMotor,
		ev3api::Motor& tailMotor)
		:mLeftMotor(leftMotor),
		 mRightMotor(rightMotor),
		 mTailMotor(tailMotor){
}

//メソッド void 左右モータ値を設定する(左右pwm値)
void MotorDrive::LRMotorDrive(int8_t leftPWM,int8_t rightPWM){
	mLeftMotor.setPWM(leftPWM);
	mRightMotor.setPWM(rightPWM);
}

//メソッド void しっぽモータ値を設定する(しっぽpwm値)
void MotorDrive::TailMotorDrive(int8_t tailPWM){
	mTailMotor.setPWM(tailPWM);
}
