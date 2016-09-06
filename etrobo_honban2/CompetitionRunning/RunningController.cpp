//走行コントローラ
#include "RunningController.h"

RunningController::RunningController(DeviceValueGet* devicevalueget,
									RunningCalculation* runningcalculation,
									MotorDrive* motordrive,
									UIGet* uiget,
									ev3api::Clock& clock
									)
	:mDeviceValueGet(devicevalueget),
	mRunningCalculation(runningcalculation),
	mMotorDrive(motordrive),
	mUIGet(uiget),
	mClock(clock)
{
}

//DV = DeviceValue
//メソッド： void 走行する（現区間の番号）
void RunningController::RunningExecute(int now_section){
	DV dv;

	//現在のデバイス値を持ってくる
	dv = mDeviceValueGet->DeviceValueGetter();

	//pwm値を演算する
	dv = mRunningCalculation->RunningCalculate(dv,now_section);

	//モーターに指示を出す
	//mMotorDrive->LRMotorDrive(dv.Lmotor_pwm,dv.Rmotor_pwm);

	//ログ出力
	char*	cLogBuff	= mUIGet->GetBlueT()->pcLogBuff;
	sprintf(cLogBuff,"%lu,%d,%d\n",
			mClock.now(),
			dv.Lmotor_pwm,
			dv.Rmotor_pwm
			);
	mUIGet->WriteLog(cLogBuff);
}

