//競技走行
#include "CompetitionRunning.h"

CompetitionRunning::CompetitionRunning(RunningController* runningcontroller,
										SectionDecisionController* sectiondecisioncontroller,
										MotorDrive* motordrive,
										UIGet* uiget,
										ev3api::Clock& clock)
	:mRunningController(runningcontroller),
	 mSectionDecisionController(sectiondecisioncontroller),
	 mMotorDrive(motordrive),
	 mUIGet(uiget),
	 mClock(clock),
	 mnow_section(0){
}

//メソッド：void 競技走行する（）
void CompetitionRunning::CompetitionRun(){

	float TAIL_ANGLE_DRIVE = 3;

	while (mnow_section < 7) {

		ev3_lcd_draw_string("running_start", 0, 60);

		//しっぽをバランス走行用に制御
		mMotorDrive->TailMotorDrive(TAIL_ANGLE_DRIVE);

		//区間判断コントローラに現区間の番号をもらう
		mnow_section = mSectionDecisionController -> SectionIdentify(mnow_section);

		//走行コントローラに投げる
		mRunningController -> RunningExecute(mnow_section);

		if (mUIGet->UIGetter().Button == 'B')
			break;

		mClock.sleep(3); /* 4msec周期起動 */

	}

	ev3_lcd_draw_string("running_end", 0, 60);






}
