//区間走行データ
#include "RunningData.h"

RunningData::RunningData(){
}

//RD = RunningData
//メソッド: RD 参照する(現区間の番号)　return 現区間走行データ
RD RunningData::referData(int now_section){

	RD rd;

	// 直線用
	double mforwardStr = 70;
	double mKPStr =0.2;

	// 曲線用
	double mforwardCur = 30;


	double mKP[7] = {mKPStr,1.4,mKPStr,1.4,1.4,1.4,1.4};
	double mKI[7] = {0.1,0.2,0.1,0.2,0.2,0.2,0.2};
	double mKD[7] = {0.02,0.02,0.02,0.02,0.02,0.02,0.02};
	float mforward[7] = {mforwardStr,mforwardCur,mforwardStr,mforwardCur,mforwardCur,mforwardCur,mforwardCur};

	rd.KP = mKP[now_section];
	rd.KI = mKI[now_section];
	rd.KD = mKD[now_section];
	rd.forward = mforward[now_section];

	return rd;
}
