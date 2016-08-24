#include "MotorDrive.h"


MotorDrive::MotorDrive(const Motor* leftMotor,
					   const Motor* rightMotor,
					   const Motor* tailMotor)
		:mLeftMotor(leftMotor),
		 mRightMotor(rightMotor),
		 mTailMotor(tailMotor){
}


void MotorDrive::LRMotorDrive(float leftPWM,float rightPWM){
}

void MotorDrive::TailMotorDrive(float tailPWM){
}
