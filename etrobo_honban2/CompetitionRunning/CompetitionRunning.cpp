//競技走行
#include "CompetitionRunning.h"

CompetitionRunning::CompetitionRunning(RunningController* RunningController,
										SectionDecisionController* SectionDecisionController)
	:mRunningController(RunningController),
	 mSectionDecisionController(SectionDecisionController),
	 mnow_section(0){
}

//メソッド：void 競技走行する（）
void CompetitionRunning::CompetitionRun(){

	mnow_section = mSectionDecisionController -> SectionIdentify(mnow_section);

	mRunningController -> RunningExecute(mnow_section);

}
