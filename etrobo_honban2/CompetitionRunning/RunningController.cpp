//走行コントローラ
#include "RunningController.h"

#include "DeviceValueGet.h"
#include "RunningCalculation.h"
#include "MotorDrive.h"


RunningController::RunningController(
				DeviceInterface* deviceinterface,
				UIGet* uiget
				)
{
	m_pDeviceInterface	= deviceinterface;
	m_pUIGet	= uiget;

	m_pDeviceValueGet	= new	DeviceValueGet(deviceinterface);
	m_pRunningCalculation	= new	RunningCalculation();
	m_pMotorDrive		= new MotorDrive(deviceinterface);
}

RunningController::~RunningController()
{
	delete	m_pDeviceValueGet;
	delete	m_pRunningCalculation;
	delete	m_pMotorDrive;
}

//DV = DeviceValue
//メソッド： void 走行する（現区間の番号）
void RunningController::RunningExecute(int now_section){
	DV dv;

	//現在のデバイス値を持ってくる
	dv = m_pDeviceValueGet->DeviceValueGetter();

	//pwm値を演算する
	dv = m_pRunningCalculation->RunningCalculate(dv,now_section);

	//モーターに指示を出す
	m_pMotorDrive->LRMotorDrive(dv.Lmotor_pwm,dv.Rmotor_pwm);

	//ログ出力
	char*	cLogBuff	= m_pUIGet->GetBlueT()->pcLogBuff;
	sprintf(cLogBuff,"%lu,%d,%d\n",
			m_pDeviceInterface->m_pCClock->now(),
			dv.Lmotor_angle,
			dv.Rmotor_angle
			);
	m_pUIGet->WriteLog(cLogBuff);
}

