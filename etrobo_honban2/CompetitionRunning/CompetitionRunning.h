#ifndef COMPETITIONRUNNING_H_
#define COMPETITIONRUNNING_H_

#include "ev3api.h"
#include "RunningController.h"
#include "SectionDecisionController.h"
#include "MotorDrive.h"
#include "UIGet.h"
#include "Clock.h"

class CompetitionRunning {
public:

	CompetitionRunning(RunningController* runningcontroller,
			SectionDecisionController* sectiondecisioncontroller,
			MotorDrive* motordrive, UIGet* guiget,
			ev3api::Clock& clock);
	void CompetitionRun();
private:

	RunningController* mRunningController;
	SectionDecisionController* mSectionDecisionController;
	MotorDrive* mMotorDrive;
	UIGet* mUIGet;
	ev3api::Clock& mClock;
	int mnow_section;

};

#endif  // COMPETITIONRUNNING_H_
