//区間判断(演算)
#include "SectionDecision.h"

SectionDecision::SectionDecision()
{
}

extern int gCourse;

//DV = DeviceValue
//SDD = SectionDecisionData
//メソッド：bool 切替判断する（デバイス値(構造体), 現区間の番号）　return 判断結果
bool SectionDecision::SwitchingDecision(DV dv, int now_section) {

	SDD sdd;
	bool result = false;

	//現区間の判断データを取ってくる
	sdd = m_SectionDecisionDataGet.SectionDecisionDataGetter(now_section);

	/*計算とか比較とか*/
	if (gCourse == 1) {//Lコースだったら
		switch (now_section) {
		// 区間1(スタート区間)
		case 0:
			result = true;
			break;
			// 区間2
		case 1:
			if (dv.Lmotor_angle > sdd.Distance) {
				result = true;
			}
			break;
			// 区間3
			case 2:
			if ((dv.Lmotor_angle - dv.Rmotor_angle) > sdd.TurningAmount) {
				result = true;
			}
			break;
			// 区間4
		case 3:
			if (dv.Lmotor_angle > sdd.Distance) {
				result = true;
			}
			break;
			// 区間5
		case 4:
			if ((dv.Lmotor_angle - dv.Rmotor_angle) < sdd.TurningAmount) {
				result = true;
			}
			break;
			// 区間6
		case 5:
			if (dv.Lmotor_angle > sdd.Distance) {
				result = true;
			}
			break;
			// 区間7
		case 6:
			if (dv.Lmotor_angle > sdd.Distance) {
				result = true;
			}
			break;
		}
	}
	else if (gCourse == 2) {//Rコースだったら
		switch (now_section) {
		// 区間1(スタート区間)
		case 0:
			result = true;
			break;
			// 区間2
		case 1:
			if (dv.Lmotor_angle > sdd.Distance) {
				result = true;
			}
			break;
		// 区間3
		case 2:
			if ((dv.Lmotor_angle - dv.Rmotor_angle) < sdd.TurningAmount) {
				result = true;
			}
			break;
		// 区間4
		case 3:
			if (dv.Lmotor_angle > sdd.Distance) {
				result = true;
			}
			break;
			// 区間5
		case 4:
			if (dv.Lmotor_angle > sdd.Distance) {
				result = true;
			}
			break;
			// 区間6
		case 5:
			if (dv.Lmotor_angle > sdd.Distance) {
				result = true;
			}
			break;
			// 区間7
		case 6:
			if (dv.Lmotor_angle > sdd.Distance) {
				result = true;
			}
			break;
		}
	}

	return result;
}
