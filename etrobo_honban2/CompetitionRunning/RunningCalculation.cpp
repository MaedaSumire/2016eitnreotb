//走行演算
#include "RunningCalculation.h"

RunningCalculation::RunningCalculation(PIDCalculation* pidcalculation,
										RunningDataGet* runningdataget)
	:mPIDCalculation(pidcalculation),
	 mRunningDataGet(runningdataget){
}

//DV = DeviceValue
//メソッド：void 走行演算する（デバイス値（構造体）、現区間の番号）
DV RunningCalculation::RunningCalculate(DV dv,int now_section){
	RD rd;
	double turn;

	//区間走行データを持ってくる
	rd = mRunningDataGet->RunningDataGetter(now_section);

	//PID計算する
	turn = mPIDCalculation->PIDCalculate(rd,dv.color);

	//すべての値を渡し、モータ出力値をポインタで格納してもらう
	balance_control((float)rd.forward, (float)turn, (float)dv.gyro,(float)dv.GYRO_OFFSET, (float)dv.Lmotor_angle,
			(float)dv.Rmotor_angle, (float)dv.volt, (int8_t *)&dv.Lmotor_pwm, (int8_t *)&dv.Rmotor_pwm);

	return dv;
}
