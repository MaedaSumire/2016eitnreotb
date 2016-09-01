#ifndef RUNNINGCALCULATION_H_
#define RUNNINGCALCULATION_H_

#include "ev3api.h"
#include "DeviceValueGet.h"
#include "PIDCalculation.h"
#include "balancer.h"
#include "RunningDataGet.h"
#include "MotorDrive.h"

class RunningCalculation {
public:

	RunningCalculation(PIDCalculation* pidcalculation,
			RunningDataGet* runningdataget);
	DV RunningCalculate(DV dv,int now_section);


private:

	PIDCalculation* mPIDCalculation;
	RunningDataGet* mRunningDataGet;

};

#endif  // RUNNINGCALCULATION_H_
