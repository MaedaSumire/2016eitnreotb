#ifndef MOTORDRIVE_H_
#define MOTORDRIVE_H_

#include "ev3api.h"
#include "Motor.h"


class MotorDrive {
public:
	
	MotorDrive(Motor* leftMotor,
			   Motor* rightMotor,
			   Motor* tailMotor);
	
	void LRMotorDrive(float leftPWM,
					  float rightPWM);
	void TailMotorDrive(float tailPWM);
	
private:
	Motor* mLeftMotor;
	Motor* mRightMotor;
	Motor* mTailMotor;
};

#endif  // MOTORDRIVE_H_
