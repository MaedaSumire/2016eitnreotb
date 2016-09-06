//区間判断(演算)
#include "SectionDecision.h"

SectionDecision::SectionDecision(SectionDecisionDataGet* sectiondecisiondataget)
	:mSectionDecisionDataGet(sectiondecisiondataget){
}

//DV = DeviceValue
//SDD = SectionDecisionData
//メソッド：bool 切替判断する（デバイス値(構造体), 現区間の番号）　return 判断結果
bool SectionDecision::SwitchingDecision(DV dv,int now_section){

	SDD sdd;
	bool result = false;

	//現区間の判断データを取ってくる
	sdd = mSectionDecisionDataGet -> SectionDecisionDataGetter(now_section);

	/*計算とか比較とか*/

	return result;
}
