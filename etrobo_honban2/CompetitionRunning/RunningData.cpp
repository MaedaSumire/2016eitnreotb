//区間走行データ
#include "RunningData.h"

RunningData::RunningData(){
}

extern int gCourse;

//RD = RunningData
//メソッド: RD 参照する(現区間の番号)　return 現区間走行データ
RD RunningData::referData(int now_section){

	RD rd;

	// スタート用
	float mforwardStart = 10;

	// 直線用
	float mforwardStr = 70;
	double mKPStr =0.2;

	// 曲線用
	float mforwardCur = 30;

	if(gCourse == 1){//Lコースだったら
		double mKP[7] = {0.3,	mKPStr,	 1.52,	mKPStr,	0.93,	mKPStr,	 0.81};
		double mKI[7] = {0.08,	   0.1,  0.06,	   0.1,	 0.2,	   0.1,	  0.2};
		double mKD[7] = {0.01,	  0.04,	0.012,	  0.08,	0.02,	  0.08,	 0.06};
		float mforward[7] = {mforwardStart, mforwardStr, mforwardCur, mforwardStr, 40, mforwardStr, 50};

		rd.KP = mKP[now_section];
		rd.KI = mKI[now_section];
		rd.KD = mKD[now_section];
		rd.forward = mforward[now_section];
	}
	else if(gCourse == 2){//Rコースだったら
		double mKP[7] = {0,	 mKPStr,	 1.4,	mKPStr,	 1.7,	mKPStr,	 1.4};
		double mKI[7] = {0, 	0.1,	 0.4,	   0.1,	 1.5,	   0.1,	 0.2};
		double mKD[7] = {0,	   0.04,	0.02,	  0.08,	0.09,	  0.08,	0.02};
		float mforward[7] = {mforwardStart, mforwardStr, mforwardCur, mforwardStr, mforwardCur, 50, mforwardCur};

		rd.KP = mKP[now_section];
		rd.KI = mKI[now_section];
		rd.KD = mKD[now_section];
		rd.forward = mforward[now_section];
	}
	else if(gCourse == 3){//階段
			double mKP[14] 		= {0.2,	0.2,  0.2,	0,	0, 	0,	0.2,  0.2,  0, 	0,	0,  0,  0.2,  0.9};
			double mKI[14] 		= {0,	  0,	0,	0,	0,	0,	  0,	0,	0,	0,	0,  0,    0, 0.08};
			double mKD[14] 		= {0,	  0,	0,	0,	0,	0,	  0,	0,	0,	0,	0,  0,    0, 0.02};
			float mforward[14] 	= {10,	 10,   10,	0,	0, 	0, 	 10,   10,	0,	0,	0,  0,   50,   30};

			rd.KP = mKP[now_section];
			rd.KI = mKI[now_section];
			rd.KD = mKD[now_section];
			rd.forward = mforward[now_section];
	}

	return rd;
}
