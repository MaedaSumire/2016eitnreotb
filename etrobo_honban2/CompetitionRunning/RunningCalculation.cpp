//走行演算
#include "RunningCalculation.h"

RunningCalculation::RunningCalculation(SectionRunningDataGet* SectionRunningDataGet,
										PIDCalculation* PIDCalculation)
	:mPIDCalculation(PIDCalculation),
	mSectionRunningDataGet(SectionRunningDataGet){
}

//メソッド：void 走行演算する（デバイス値（構造体）、現区間の番号）
void RunningCalculation::RunningCalculate(DeviceValue dv,int now_section){
	SRD srd;
	double turn;

	//区間走行データを持ってくる
	srd = mSectionRunningDataGet->SectionRunningDataGetter(now_section);

	//PID計算する
	turn = mPIDCalculation->PIDCalculate(srd,dv.color);

	//すべての値を注ぎ込み、モータ出力値をポインタで格納してもらう
	balance_control(srd.forward, turn, dv.gyro,dv.GYRO_OFFSET, dv.Lmotor_angle,
			dv.Rmotor_angle, dv.volt, &dv.Lmotor_pwm, &dv.Rmotor_pwm);
}
