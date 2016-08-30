#ifndef SECTIONDECISION_H_
#define SECTIONDECISION_H_

#include "ev3api.h"
#include "SectionDecisionDataGet.h"
#include "SectionDecisionData.h"
#include "DeviceValueGet.h"

class SectionDecision {
public:

	SectionDecision(SectionDecisionDataGet* SectionDecisionDataGet);
	bool SwitchingDecision(DeviceValue dv,int now_section);

private:

	SectionDecisionDataGet* mSectionDecisionDataGet;

};

#endif  // SECTIONDECISION_H_
