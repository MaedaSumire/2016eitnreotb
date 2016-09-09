#ifndef SECTIONDECISION_H_
#define SECTIONDECISION_H_

#include "ev3api.h"
#include "SectionDecisionDataGet.h"
#include "SectionDecisionData.h"
#include "DeviceValueGet.h"

class SectionDecision {
public:

	SectionDecision();
	bool SwitchingDecision(DV dv,int now_section);

private:

	SectionDecisionDataGet m_SectionDecisionDataGet;

};

#endif  // SECTIONDECISION_H_
