#include "MotorDrive.h"

MotorDrive::MotorDrive(ev3api::Motor& leftMotor,
		ev3api::Motor& rightMotor,
		ev3api::Motor& tailMotor)
		:mLeftMotor(leftMotor),
		 mRightMotor(rightMotor),
		 mTailMotor(tailMotor){
}

//左右車輪にモーター値（PWM値）出力
void MotorDrive::LRMotorDrive(int8_t leftPWM,int8_t rightPWM){
	mLeftMotor.setPWM(leftPWM);
	mRightMotor.setPWM(rightPWM);
}

//しっぽモーターにモーター理（PWM値）出力
void MotorDrive::TailMotorDrive(int8_t tailPWM){
	mTailMotor.setPWM(tailPWM);
}
