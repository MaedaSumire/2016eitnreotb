//区間走行データ
#include "RunningData.h"

RunningData::RunningData(){
}

//RD = RunningData
//メソッド: RD 参照する(現区間の番号)　return 現区間走行データ
RD RunningData::referData(int now_section){

	RD rd;

	double mKP[7] = {1.4,1.4,1.4,1.4,1.4,1.4,1.4};
	double mKI[7] = {0.2,0.2,0.2,0.2,0.2,0.2,0.2};
	double mKD[7] = {0.02,0.02,0.02,0.02,0.02,0.02,0.02};
	float mforward[7] = {30,30,30,30,30,30,30};

	rd.KP = mKP[now_section];
	rd.KI = mKI[now_section];
	rd.KD = mKD[now_section];
	rd.forward = mforward[now_section];

	return rd;
}
