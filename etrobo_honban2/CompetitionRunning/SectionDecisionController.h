#ifndef SECTIONDECISIONCONTROLLER_H_
#define SECTIONDECISIONCONTROLLER_H_

#include "ev3api.h"
#include "DeviceInterface.h"
#include "SectionDecision.h"
#include "DeviceValueGet.h"

class SectionDecisionController {
public:

	SectionDecisionController(
			DeviceInterface* pDeviceInterface
			);

	~SectionDecisionController();

	int SectionIdentify(int now_section);

private:
	DeviceValueGet* m_pDeviceValueGet;

	SectionDecision m_SectionDecision;
};

#endif  // SECTIONDECISIONCONTROLLER_H_
