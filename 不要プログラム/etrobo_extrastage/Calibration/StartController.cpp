//スタートコントローラ
#include "StartController.h"

StartController::StartController(
		CalibrationController*	calibrationcontroller,
		MotorDrive* motordrive,
		UIGet* uiget,
		ev3api::Clock& clock)
	:mCalibrationController(calibrationcontroller),
	 mMotorDrive(motordrive),
	 mUIGet(uiget),
	 mClock(clock){
}

//メソッド： void スタート判断する（）
void StartController::StartDicision(){

	//画面出力（削除可）
	ev3_lcd_draw_string("taiki_start", 0, 40);

	CALIBRAT	calibrat	= mCalibrationController->GetValue();	// キャリブレーション値取得

	//スタート指示があるまでループ
	while(1){

		UI ui	= mUIGet->UIGetter();	// ループ１回につきUIGetterは１回にしないと取得できない

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

		mMotorDrive->TailMotorDrive(calibrat.TailAngleStandUp);

		mClock.sleep(10);

	}

	mCalibrationController->SetValue( calibrat );	// キャリブレーション値設定

	//画面出力（削除可）
	ev3_lcd_draw_string("taiki_end", 0, 50);

}

