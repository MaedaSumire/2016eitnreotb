//走行演算
#include "RunningCalculation.h"

RunningCalculation::RunningCalculation(SectionRunningDataGet* SectionRunningDataGet,
										PIDCalculation* PIDCalculation)
	:mPIDCalculation(PIDCalculation),
	mSectionRunningDataGet(SectionRunningDataGet){
}

//メソッド：void 走行演算する（デバイス値（構造体）、現区間の番号）
DeviceValue RunningCalculation::RunningCalculate(DeviceValue dv,int now_section){
	SRD srd;
	double turn;

	//区間走行データを持ってくる
	srd = mSectionRunningDataGet->SectionRunningDataGetter(now_section);

	//PID計算する
	turn = mPIDCalculation->PIDCalculate(srd,dv.color);

	//すべての値を渡し、モータ出力値をポインタで格納してもらう
	balance_control((float)srd.forward, (float)turn, (float)dv.gyro,(float)dv.GYRO_OFFSET, (float)dv.Lmotor_angle,
			(float)dv.Rmotor_angle, (float)dv.volt, (int8_t *)&dv.Lmotor_pwm, (int8_t *)&dv.Rmotor_pwm);

	return dv;
}
