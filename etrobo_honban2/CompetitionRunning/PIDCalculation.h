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
	double PIDCalculate(struct SRD SectionRunningData,int8_t DeviceBrightness);

private:
	static double diff[2];
	static double	integral;
	double p, i, d;
	int32_t nBri;
	double KP,KI,KD;

	int8_t mBlack;
	int8_t mWhite;
	int8_t mGray;

};

#endif  // PIDCALCULATION_H_
