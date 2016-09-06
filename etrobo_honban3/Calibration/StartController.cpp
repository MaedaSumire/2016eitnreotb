//スタートコントローラ
#include "StartController.h"

//StartController::StartController(StartInstructionGet* startinstructionget,
//		PostureAdjustment* postureadjustment,
//		ev3api::Clock& clock)
//	:mStartInstructionGet(startinstructionget),
//	 mPostureAdjustment(postureadjustment),
//	 mClock(clock){
//}

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

//	bool result = false;

	//画面出力（削除可）
	ev3_lcd_draw_string("taiki_start", 0, 30);

	CALIBRAT	calibrat	= mCalibrationController->GetValue();	// キャリブレーション値取得

	//スタート指示があるまでループ
	while(1){

		UI ui	= mUIGet->UIGetter();	// ループ１回につきUIGetterは１回にしないと取得できない

		// しっぽ角度調整クラスPostureAdjustment()は使用しない
		// 理由：PostureAdjust()内で呼ばれるUIGetter()が干渉して動作しない為
		//     同様にStartInstructionGet()も使用しない
		//
		////しっぽ調整機能
		//mPostureAdjustment -> PostureAdjust();
		//
		//スタート指示の有無を受け取る
		//result = mStartInstructionGet -> StartInstructionGetter();
		//スタート指示があればbreak
		//if(result){
		//	break;
		//}

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
	ev3_lcd_draw_string("taiki_end", 0, 40);

}

