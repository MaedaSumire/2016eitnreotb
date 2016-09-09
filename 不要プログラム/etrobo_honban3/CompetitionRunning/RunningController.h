#ifndef RUNNINGCONTROLLER_H_
#define RUNNINGCONTROLLER_H_

#include "ev3api.h"
#include "DeviceValueGet.h"
#include "RunningCalculation.h"
#include "MotorDrive.h"
#include "Clock.h"
#include "UIGet.h"

class RunningController {
public:

	RunningController(DeviceValueGet* devicevalueget,
					RunningCalculation* runningcalculation,
					MotorDrive* motordrive,
					UIGet* uiget,
					ev3api::Clock& clock
					);

	void RunningExecute(int now_section);


private:
	DeviceValueGet* mDeviceValueGet;
	RunningCalculation* mRunningCalculation;
	MotorDrive* mMotorDrive;

	UIGet* mUIGet;
	ev3api::Clock& mClock;
};

#endif  // RUNNINGCALCULATION_H_
