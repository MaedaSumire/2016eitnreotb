#ifndef EXTRASTAGELOOKUP_H_
#define EXTRASTAGELOOKUP_H_

#include "ev3api.h"
#include "RunningController.h"
#include "SectionDecisionController.h"
#include "MotorDrive.h"
#include "UIGet.h"
#include "Clock.h"

class ExtraStageLookUp {
public:

	ExtraStageLookUp(MotorDrive* motordrive, DeviceValueGet* devicevalueget, ev3api::Clock& clock);
	void ExtraRun();

private:

	MotorDrive* mMotorDrive;
	DeviceValueGet* mDeviceValueGet;
	ev3api::Clock& mClock;

};

#endif  // EXTRASTAGELOOKUP_H_
