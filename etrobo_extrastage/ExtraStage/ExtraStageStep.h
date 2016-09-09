#ifndef EXTRASTAGESTEP_H_
#define EXTRASTAGESTEP_H_

#include "ev3api.h"
#include "PIDCalculation.h"
#include "SectionDecisionData.h"
#include "RunningData.h"
#include "RunningCalculation.h"
#include "MotorDrive.h"
#include "balancer.h"
#include "Clock.h"

class ExtraStageStep {
public:

	ExtraStageStep(MotorDrive* motordrive, DeviceValueGet* devicevalueget, PIDCalculation* pidcalculation,
			RunningCalculation* runningcalculate,ev3api::Clock& clock);
	void ExtraRun();

private:

	MotorDrive* mMotorDrive;
	DeviceValueGet* mDeviceValueGet;
	PIDCalculation* mPIDCalculation;
	RunningCalculation* mRunningCalculation;
	ev3api::Clock& mClock;


};

#endif  // EXTRASTAGESTEP_H_
