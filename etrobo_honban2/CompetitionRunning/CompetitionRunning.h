#ifndef COMPETITIONRUNNING_H_
#define COMPETITIONRUNNING_H_

#include "ev3api.h"
#include "RunningController.h"
#include "SectionDecisionController.h"

class CompetitionRunning {
public:

	CompetitionRunning(RunningController* RunningController,
			SectionDecisionController* SectionDecisionController);
	void CompetitionRun();
private:

	RunningController* mRunningController;
	SectionDecisionController* mSectionDecisionController;
	int mnow_section;

};

#endif  // COMPETITIONRUNNING_H_
