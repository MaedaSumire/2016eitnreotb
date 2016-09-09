#ifndef RUNNINGDATA_H_
#define RUNNINGDATA_H_

#include "ev3api.h"
#include "CalibrationController.h"

typedef struct{
	double KP;
	double KI;
	double KD;
	float forward;
} RD ;



class RunningData {
public:

	RunningData();
	RD referData(int now_section);

private:

	double mKP[7];
	double mKI[7];
	double mKD[7];
	float mforward[7];

};

#endif  // SECTIONRUNNINGDATA_H_
