#ifndef PIDCALCULATION_H_
#define PIDCALCULATION_H_

#include "ev3api.h"
#include "SectionRunningData.h"

//PID制御用
#define DELTA_T	0.004


class PIDCalculation {
public:

	PIDCalculation();

	void Calibrate(int8_t DBBlack, int8_t DBWhite, int8_t DBGray);
	double PIDCalculate(SRD SectionRunningData,int8_t DeviceBrightness);

private:
	int8_t mBlack;
	int8_t mWhite;
	int8_t mGray;

	double diff1;
	double diff2;
	double	integral;
	double p, i, d;
	double turn;
	int32_t nBri;

};

#endif  // PIDCALCULATION_H_
