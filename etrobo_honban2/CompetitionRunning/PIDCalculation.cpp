//PID演算

#include "PIDCalculation.h"

PIDCalculation::PIDCalculation()
	:mBlack(0.0),
	 mWhite(40.0),
	 mGray(20.0),
	diff1(0),
	diff2(0),
	integral(0),
	p(0),
	i(0),
	d(0),
	turn(0),
	nBri(26)
		{
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
//メソッド: PID演算結果値(turn値) PID演算する(区間走行データ、デバイス値)
double PIDCalculation::PIDCalculate(SRD srd,int8_t DeviceBrightness){


	//PID
	diff1 = diff2;
	diff2 = nBri - DeviceBrightness;
	integral += (diff2 + diff1) / 2.0 * DELTA_T;

	p = srd.KP * diff2;
	i = srd.KI * integral;
	d = srd.KD * (diff2 - diff1) / DELTA_T;

	turn = p + i + d;

	if(turn < -100.0 ){
		turn = -100.0;
	}else if (turn > 100.0){
		turn = 100.0;
	}

	return turn;

}
