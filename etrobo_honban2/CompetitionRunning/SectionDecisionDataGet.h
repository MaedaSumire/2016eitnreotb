#ifndef SECTIONDECISIONDATAGET_H_
#define SECTIONDECISIONDATAGET_H_

#include "ev3api.h"
#include "SectionDecisionData.h"

class SectionDecisionDataGet {
public:

	SectionDecisionDataGet(SectionDecisionData* sectiondecisiondata);
	SDD SectionDecisionDataGetter(int now_section);


private:

	SectionDecisionData* mSectionDecisionData;

};

#endif  // SECTIONDECISIONDATAGET_H_
