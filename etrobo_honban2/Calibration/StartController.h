#ifndef STARTCONTROLLER_H_
#define STARTCONTROLLER_H_

#include "ev3api.h"
#include "Clock.h"
#include "CalibrationController.h"

class StartController {
public:

	StartController(
			CalibrationController*	calibrationcontroller,
			MotorDrive* motordrive,
			UIGet* uiget,
			ev3api::Clock& clock );

	void StartDicision();

private:
	ev3api::Clock& mClock;
	CalibrationController* mCalibrationController;
	MotorDrive* mMotorDrive;
	UIGet* mUIGet;
};

#endif  // STARTCONTROLLER_H_
