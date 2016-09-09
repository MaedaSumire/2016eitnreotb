#ifndef PIDCALCULATION_H_
#define PIDCALCULATION_H_

#include "ev3api.h"
#include "RunningData.h"
#include "CalibrationController.h"

//PID制御用
#define DELTA_T	0.004


class PIDCalculation {
public:

	PIDCalculation();

	void Calibrate();
	double PIDCalculate(RD rd,int8_t DeviceBrightness);

private:
	int8_t mBlack;
	int8_t mWhite;
	int8_t mHalf;

	double diff1;
	double diff2;
	double integral;
	double p, i, d;
	double turn;

};

#endif  // PIDCALCULATION_H_
