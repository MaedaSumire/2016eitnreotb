#include "PIDCalculation.h"



PIDCalculation::PIDCalculation()
	:mBlack(0.0),
	 mWhite(40.0),
	 mGray(20.0){
}

//DB = DeviceBrightness
//キャリブレーション時に取得した黒・白・灰色の値を格納
void PIDCalculation::Calibrate(int8_t DBBlack, int8_t DBWhite, int8_t DBGray){
	mBlack = DBBlack;
	mWhite = DBWhite;
	mGray = DBGray;
}


//SRD = SectionRunningData
//PID計算後、turn値を返却
double PIDCalculation::PIDCalculate(struct SRD SectionRunningData,int8_t DeviceBrightness){

	static double diff[2];
	static double	integral;
	double p, i, d;
	int32_t nBri;
	double turn;

	//PID
	diff[0] = diff[1];
	diff[1] = nBri - g_unBrightness;
	integral += (diff[1] + diff[0]) / 2.0 * DELTA_T;

	p = SRD.KP * diff[1];
	i = SRD.KI * integral;
	d = SRD.KD * (diff[1] - diff[0]) / DELTA_T;

	turn = p + i + d;

	if(turn < -100 ){
		turn = -100;
	}else if (turn > 100){
		turn = 100;
	}

	return turn;

}
