//区間判断データ
#include "SectionDecisionData.h"

SectionDecisionData::SectionDecisionData(){
}

//SDD = SectionDecisionData
//メソッド: 参照する
SDD SectionDecisionData::referData(int now_section){

	SDD sdd;

	double mD[7] = {10.0,10.0,10.0,10.0,10.0,10.0,10.0};
	double mTA[7] = {10.0,10.0,10.0,10.0,10.0,10.0,10.0};

	sdd.Distance = mD[now_section];
	sdd.TurningAmount = mTA[now_section];

	return sdd;
}
