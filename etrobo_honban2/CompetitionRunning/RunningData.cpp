//区間走行データ
#include "RunningData.h"

RunningData::RunningData() {
}

extern int gCourse;

//RD = RunningData
//メソッド: RD 参照する(現区間の番号)　return 現区間走行データ
RD RunningData::referData(int now_section) {

	RD rd;

	if (gCourse == 1) { //Lコースだったら
					//seciton	0		1		2		3		4		5		6
		double mKP[7] 		= { 0.3, 	0.2,	1.5,	0.2,	0.85,	0.2,	0.81 };
		double mKI[7] 		= { 0.08,	0.1,	0.06,	0.1,	0.2,	0.1,	0.2 };
		double mKD[7] 		= { 0.01,	0.04,	0.012,	0.04,	0.02,	0.08,	0.06 };
		float mforward[7] 	= { 10,		70,		30,		70,		40,		70,		50 };

		rd.KP = mKP[now_section];
		rd.KI = mKI[now_section];
		rd.KD = mKD[now_section];
		rd.forward = mforward[now_section];
	} else if (gCourse == 2) { //Rコースだったら
					//seciton	0		1		2		3		4		5		6
		double mKP[7] 		= { 0.3,	0.2,	1.4,	0.2,	1.7,	0.2,	1.4 };
		double mKI[7] 		= { 0.08,	0.1,	0.4,	0.1,	1.5,	0.1,	0.2 };
		double mKD[7] 		= { 0.01,	0.04,	0.02,	0.08,	0.09,	0.08,	0.02 };
		float mforward[7] 	= { 10,		70,		30,		60,		30,		50,		30 };

		rd.KP = mKP[now_section];
		rd.KI = mKI[now_section];
		rd.KD = mKD[now_section];
		rd.forward = mforward[now_section];
	} else if (gCourse == 3) { //階段
					//seciton	0		1		2		3	4	5	6		7	8	9	10	11	12		13
		double mKP[14] 		= { 0.2,	0.2,	0.2,	0, 	0,	0,	1.0,	1.0,0,	0,	0,	0,	0.2,	0.9 };
		double mKI[14] 		= { 0,		0,		0,		0,	0,	0,	0,		0,	0,	0,	0,	0,	0,		0.08 };
		double mKD[14] 		= { 0,		0,		0,		0, 	0,	0,	0,		0,	0,	0,	0,	0,	0,		0.02 };
		float mforward[14] 	= { 10,		10,		0,		0, 	0,	0,	10,		10,	0,	0,	0,	0,	10,		30 };

		rd.KP = mKP[now_section];
		rd.KI = mKI[now_section];
		rd.KD = mKD[now_section];
		rd.forward = mforward[now_section];
	}

	// ルックアップゲート
	else if (gCourse == 4) {
		double mKP[1] = { 0.2 };
		double mKI[1] = { 0};
		double mKD[1] = { 0};
		float mforward[1] = { 0};

		rd.KP = mKP[now_section];
		rd.KI = mKI[now_section];
		rd.KD = mKD[now_section];
		rd.forward = mforward[now_section];

	}

	return rd;
}
