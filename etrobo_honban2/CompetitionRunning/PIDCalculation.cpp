//PID演算

#include "PIDCalculation.h"

PIDCalculation::PIDCalculation()
	:mBlack(1),
	 mWhite(34),
	 mHalf(22),
	 diff1(0),
	 diff2(0),
	 integral(0),
	 p(0),
	 i(0),
	 d(0),
	 turn(0){

}

//DB = DeviceBrightness
//キャリブレーション時に取得した黒・白・灰色の値を格納
void PIDCalculation::Calibrate(){
	//mBlack = calibrat.Black;
	//mWhite = calibrat.White;
	//mHalf = calibrat.Half;
}


//SRD = SectionRunningData
//PID計算後、turn値を返却
//メソッド: PID演算結果値(turn値) PID演算する(区間走行データ、デバイス値)
double PIDCalculation::PIDCalculate(RD rd,int8_t DeviceBrightness){


	//PID
	diff1 = diff2;
	diff2 = mHalf - DeviceBrightness;
	integral += (diff2 + diff1) / 2.0 * DELTA_T;

	p = rd.KP * diff2;
	i = rd.KI * integral;
	d = rd.KD * (diff2 - diff1) / DELTA_T;

	turn = p + i + d;

	if(turn < -100.0 ){
		turn = -100.0;
	}else if (turn > 100.0){
		turn = 100.0;
	}

	return turn;

}
