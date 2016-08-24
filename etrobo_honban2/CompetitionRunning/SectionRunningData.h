#ifndef SECTIONRUNNINGDATA_H_
#define SECTIONRUNNINGDATA_H_

#include "ev3api.h"

typedef struct{
	double KP;
	double KI;
	double KD;
	double forward;
} SRD ;

class SectionRunningData {
public:

	SectionRunningData();
	SRD referData(int now_section);

private:
	double mKP[7];
	double mKI[7];
	double mKD[7];
	double mforward[7];
};

#endif  // SECTIONRUNNINGDATA_H_
