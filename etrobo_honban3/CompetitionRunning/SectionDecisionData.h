#ifndef SECTIONDICISIONDATA_H_
#define SECTIONDICISIONDATA_H_

#include "ev3api.h"

typedef struct{
	double Distance;
	double TurningAmount;
} SDD ;

class SectionDecisionData {
public:

	SectionDecisionData();
	SDD referData(int now_section);

private:

};

#endif  // SECTIONDICISIONDATA_H_
