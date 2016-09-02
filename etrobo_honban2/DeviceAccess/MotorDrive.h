#ifndef MOTORDRIVE_H_
#define MOTORDRIVE_H_

#include "ev3api.h"
#include "Motor.h"


class MotorDrive {
public:
	
	MotorDrive(ev3api::Motor& leftmotor,
			   ev3api::Motor& rightmotor,
			   ev3api::Motor& tailmotor);
	
	void LRMotorDrive(	int8_t leftPWM,
						int8_t rightPWM);
	void TailMotorDrive(float angle);
	
private:
	ev3api::Motor& mLeftMotor;
	ev3api::Motor& mRightMotor;
	ev3api::Motor& mTailMotor;
};

#endif  // MOTORDRIVE_H_
