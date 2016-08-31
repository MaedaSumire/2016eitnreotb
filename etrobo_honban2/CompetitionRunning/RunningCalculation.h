#ifndef RUNNINGCALCULATION_H_
#define RUNNINGCALCULATION_H_

#include "ev3api.h"
#include "DeviceValueGet.h"
#include "PIDCalculation.h"
#include "balancer.h"
#include "SectionRunningDataGet.h"
#include "MotorDrive.h"

class RunningCalculation {
public:

	RunningCalculation(SectionRunningDataGet* SectionRunningDataGet,
			PIDCalculation* PIDCalculation);
	DeviceValue RunningCalculate(DeviceValue dv,int now_section);


private:

	PIDCalculation* mPIDCalculation;
	SectionRunningDataGet* mSectionRunningDataGet;

};

#endif  // RUNNINGCALCULATION_H_
