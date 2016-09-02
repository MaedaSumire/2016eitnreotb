//キャリブレーションコントローラ
#include "CalibrationController.h"

CalibrationController::CalibrationController(ev3api::GyroSensor& gyrosensor,
											ev3api::Motor& leftmotor,
											ev3api::Motor& rightmotor,
											ev3api::Motor& tailmotor,
											ev3api::Clock& clock,
											PostureAdjustment* postureadjustment,
											ColorGet* colorget,
											UIGet* uiget)
	:mGyroSensor(gyrosensor),
	 mLeftMotor(leftmotor),
	 mRightMotor(rightmotor),
	 mTailMotor(tailmotor),
	 mClock(clock),
	 mPostureAdjustment(postureadjustment),
	 mColorGet(colorget),
	 mUIGet(uiget){
}

//CC = CalibrateColor 黒色・白色の輝度
//メソッド： void キャリブレーションする（）
void CalibrationController::Calibrate(){
	CC cc;

	//画面出力（削除可）
	ev3_lcd_draw_string("calibration_start", 0, 0);

	//センサ・モータを初期化する
	SensorMotorinit();

	//終了条件に達するまで姿勢調節・輝度取得を実施
	while(mUIGet->UIGetter().Button != 'E'){
		mPostureAdjustment -> PostureAdjust();

		//cc = mColorGet -> ColorGetter();

		mClock.sleep(10);
	}
	//画面出力（削除可）
	ev3_lcd_draw_string("calibration_end", 0, 10);

}

//メソッド: void センサ・モータを初期化する()
void CalibrationController::SensorMotorinit(){
	mGyroSensor.reset();
	mLeftMotor.reset();
	mRightMotor.reset();
	mTailMotor.reset();
}
