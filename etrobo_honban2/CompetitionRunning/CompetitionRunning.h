#ifndef COMPETITIONRUNNING_H_
#define COMPETITIONRUNNING_H_

#include "DeviceInterface.h"
#include "RunningController.h"
#include "SectionDecisionController.h"
#include "UIGet.h"
#include "Clock.h"

class CompetitionRunning {
public:
	CompetitionRunning(
			DeviceInterface* pDeviceInterface,
			UIGet* guiget
			);

	void CompetitionRun();
private:

	DeviceInterface* m_pDeviceInterface;

	UIGet* m_pUIGet;

	int m_nNowSection;	// åªãÊä‘î‘çÜ

};

#endif  // COMPETITIONRUNNING_H_
