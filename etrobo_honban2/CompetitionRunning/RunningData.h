#ifndef RUNNINGDATA_H_
#define RUNNINGDATA_H_

#include "ev3api.h"

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

};

#endif  // SECTIONRUNNINGDATA_H_
