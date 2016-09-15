//区間判断データ
#include "SectionDecisionData.h"

SectionDecisionData::SectionDecisionData(){
}

extern int gCourse;

//SDD = SectionDecisionData
//メソッド: 参照する
SDD SectionDecisionData::referData(int now_section){

	SDD sdd;

	if(gCourse == 1){//Lコースだったら
		double mD[7] = 	{100.0,	3300.0,	0.0,	6400.0,	0.0,	8700.0,	12000.0};
		double mTA[7] = {10.0,	0.0,	730.0,	0.0,	390.0,	0.0,	0.0};
		sdd.Distance = mD[now_section];
		sdd.TurningAmount = mTA[now_section];
	}
	else if(gCourse == 2){//Rコースだったら
		double mD[7] =  {10.0,	3700.0,	0.0,	6500.0,	7900.0,	9300.0,	11200.0};
		double mTA[7] = {10.0,	0.0,	-370.0,	0.0,	0.0,	0.0,	0.0};
		sdd.Distance = mD[now_section];
		sdd.TurningAmount = mTA[now_section];
	}
	return sdd;
}
