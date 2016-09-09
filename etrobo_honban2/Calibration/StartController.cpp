//スタートコントローラ
#include "StartController.h"

StartController::StartController(
		DeviceInterface* 		pDeviceInterface,
		CalibrationController*	calibrationcontroller,
		UIGet* uiget)
	:m_pDeviceInterface(pDeviceInterface),
	 m_pCalibrationController(calibrationcontroller),
	 m_pUIGet(uiget)
{
	m_pMotorDrive	= new MotorDrive(pDeviceInterface);
}

StartController::~StartController()
{
	delete	m_pMotorDrive;
}

//メソッド： void スタート判断する（）
void StartController::StartDicision(){

	//画面出力（削除可）
	ev3_lcd_draw_string("taiki_start", 0, 30);

	CALIBRAT	calibrat	= m_pCalibrationController->GetValue();	// キャリブレーション値取得

	//スタート指示があるまでループ
	while(1){

		UI ui	= m_pUIGet->UIGetter();	// ループ１回につきUIGetterは１回にしないと取得できない

		if (ui.touch || ui.btcKey == '1'){
			break;	// スタート指示
		}

		//しっぽ調整機能
		if ( ui.Button == 'U' ){
			calibrat.TailAngleStandUp += 0.05;
		}
		else if (ui.Button == 'D'){
			calibrat.TailAngleStandUp -= 0.05;
		}

		m_pMotorDrive->TailMotorDrive(calibrat.TailAngleStandUp);

		m_pDeviceInterface->m_pCClock->sleep(10);

	}

	m_pCalibrationController->SetValue( calibrat );	// キャリブレーション値設定

	//画面出力（削除可）
	ev3_lcd_draw_string("taiki_end", 0, 40);

}

