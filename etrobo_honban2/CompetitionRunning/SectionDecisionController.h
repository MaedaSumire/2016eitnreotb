#ifndef SECTIONDECISIONCONTROLLER_H_
#define SECTIONDECISIONCONTROLLER_H_

#include "ev3api.h"
#include "SectionDecision.h"
#include "DeviceValueGet.h"

class SectionDecisionController {
public:

	SectionDecisionController(SectionDecision* SectionDecision,
			DeviceValueGet* DeviceValueGet);
	int SectionIdentify(int now_section);

private:

	SectionDecision* mSectionDecision;
	DeviceValueGet* mDeviceValueGet;
};

#endif  // SECTIONDECISIONCONTROLLER_H_
