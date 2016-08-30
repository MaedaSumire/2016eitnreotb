//競技走行
#include "CompetitionRunning.h"

CompetitionRunning::CompetitionRunning(RunningController* runningcontroller,
										SectionDecisionController* sectiondecisioncontroller)
	:mRunningController(runningcontroller),
	 mSectionDecisionController(sectiondecisioncontroller),
	 mnow_section(0){
}

//メソッド：void 競技走行する（）
void CompetitionRunning::CompetitionRun(){

	//区間判断コントローラに現区間の番号をもらう
	mnow_section = mSectionDecisionController -> SectionIdentify(mnow_section);

	//走行コントローラに投げる
	mRunningController -> RunningExecute(mnow_section);

}
