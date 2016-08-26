#ifndef RUNNINGCONTROLLER_H_
#define RUNNINGCONTROLLER_H_

#include "ev3api.h"
#include "DeviceValueGet.h"
#include "RunningCalculation.h"
#include "MotorDrive.h"

class RunningController {
public:

	RunningController(DeviceValueGet* DeviceValueGet,
					RunningCalculation* RunningCalculation,
					MotorDrive* MotorDrive);
	int8_t RunningExecute(int now_section);


private:
	DeviceValueGet* mDeviceValueGet;
	RunningCalculation* mRunningCalculation;
	MotorDrive* mMotorDrive;
};

#endif  // RUNNINGCALCULATION_H_
