//走行コントローラ
#include "RunningController.h"

RunningController::RunningController(DeviceValueGet* DeviceValueGet,
									RunningCalculation* RunningCalculation,
									MotorDrive* MotorDrive)
	:mDeviceValueGet(DeviceValueGet),
	mRunningCalculation(RunningCalculation),
	mMotorDrive(MotorDrive){
}

//メソッド： void 走行する（現区間の番号）
void RunningController::RunningExecute(int now_section){
	DeviceValue dv;

	//現在のデバイス値を持ってくる
	dv = mDeviceValueGet->DeviceValueGetter();

	//pwm値を演算する
	mRunningCalculation->RunningCalculate(dv,now_section);

	//モーターに指示を出す
	mMotorDrive->LRMotorDrive(dv.Lmotor_pwm,dv.Rmotor_pwm);
}
