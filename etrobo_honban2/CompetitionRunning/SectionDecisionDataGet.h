#ifndef SECTIONDECISIONDATAGET_H_
#define SECTIONDECISIONDATAGET_H_

#include "ev3api.h"
#include "SectionDecisionData.h"

class SectionDecisionDataGet {
public:

	SectionDecisionDataGet();

	SDD SectionDecisionDataGetter(int now_section);


private:

	SectionDecisionData m_SectionDecisionData;

};

#endif  // SECTIONDECISIONDATAGET_H_
