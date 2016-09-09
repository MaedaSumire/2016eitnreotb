//競技走行
#include "CompetitionRunning.h"

CompetitionRunning::CompetitionRunning(
		DeviceInterface* pDeviceInterface,
		UIGet* guiget
		)
{
	m_pDeviceInterface	= pDeviceInterface;
	m_pUIGet			= guiget;
	m_nNowSection		= 0;	// 現在の区間番号
}

//メソッド：void 競技走行する（）
void CompetitionRunning::CompetitionRun(){

	float TAIL_ANGLE_DRIVE = 3;

	MotorDrive					motorDrive( m_pDeviceInterface );
	SectionDecisionController	sectionDecisionController( m_pDeviceInterface );
	RunningController			runningController( m_pDeviceInterface, m_pUIGet );

	while (m_nNowSection < 7) {

		ev3_lcd_draw_string("running_start", 0, 60);

		//しっぽをバランス走行用に制御
		motorDrive.TailMotorDrive(TAIL_ANGLE_DRIVE);

		//区間判断コントローラに現区間の番号をもらう
		m_nNowSection = sectionDecisionController.SectionIdentify(m_nNowSection);

		//走行コントローラに投げる
		runningController.RunningExecute(m_nNowSection);

		if (m_pUIGet->UIGetter().Button == 'B')
			break;

		m_pDeviceInterface->m_pCClock->sleep(3); /* 4msec周期起動 */

	}

	ev3_lcd_draw_string("running_end", 0, 60);






}
