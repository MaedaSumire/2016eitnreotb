#ifndef SECTIONRUNNINGDATA_H_
#define SECTIONRUNNINGDATA_H_

#include "ev3api.h"
#include "SectionRunningData.h"

typedef struct{
	double KP;
	double KI;
	double KD;
	float forward;
} SRD ;

class SectionRunningData {
public:

	SectionRunningData();
	SRD referData(int now_section);

private:

};

#endif  // SECTIONRUNNINGDATA_H_
