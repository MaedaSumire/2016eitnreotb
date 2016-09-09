//現区間判断データ取得
#include "SectionDecisionDataGet.h"

SectionDecisionDataGet::SectionDecisionDataGet()
{
}

//SDD = SectionDecisionData
//メソッド: SDD 現区間判断データを取得する(現区間の番号) return 現区間判断データ
SDD SectionDecisionDataGet::SectionDecisionDataGetter(int now_section){

	SDD sdd;

	sdd = m_SectionDecisionData.referData(now_section);

	return sdd;
}
