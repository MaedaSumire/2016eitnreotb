#ifndef CALIBRATIONCONTROLLER_H_
#define CALIBRATIONCONTROLLER_H_

#include "ev3api.h"
#include "Motor.h"
#include "GyroSensor.h"
#include "PostureAdjustment.h"
#include "ColorGet.h"

class CalibrationController {
public:

	CalibrationController(ev3api::GyroSensor& gyrosensor, ev3api::Motor& leftmotor,
							ev3api::Motor& rightmotor, ev3api::Motor& tailmotor,
							PostureAdjustment* postureadjustment, ColorGet* colorget);
	void RunningExecute(int now_section);
	void Calibrate();

private:
	void SensorMotorinit();

	ev3api::GyroSensor& mGyroSensor;
	ev3api::Motor& mLeftMotor;
	ev3api::Motor& mRightMotor;
	ev3api::Motor& mTailMotor;
	PostureAdjustment* mPostureAdjustment;
	ColorGet* mColorGet;

};

#endif  // CALIBRATIONCONTROLLER_H_
