//キャリブレーションコントローラ
#include "CalibrationController.h"

CalibrationController::CalibrationController(ev3api::GyroSensor& gyrosensor,
											ev3api::Motor& leftmotor,
											ev3api::Motor& rightmotor,
											ev3api::Motor& tailmotor,
											ev3api::Clock& clock,
											PostureAdjustment* postureadjustment,
											ColorGet* colorget)
	:mGyroSensor(gyrosensor),
	 mLeftMotor(leftmotor),
	 mRightMotor(rightmotor),
	 mTailMotor(tailmotor),
	 mClock(clock),
	 mPostureAdjustment(postureadjustment),
	 mColorGet(colorget){
}

//CC = CalibrateColor 黒色・白色の輝度
//メソッド： void キャリブレーションする（）
void CalibrationController::Calibrate(){
	CC cc;

	//センサ・モータを初期化する
	SensorMotorinit();

	//終了条件に達するまで姿勢調節・輝度取得を実施
	while(1){
		ev3_lcd_draw_string("calibration_while", 0, 10);
		mPostureAdjustment -> PostureAdjust();

		//cc = mColorGet -> ColorGetter();

		mClock.sleep(10);
	}
	ev3_lcd_draw_string("calibration_end", 0, 4);


}

//メソッド: void センサ・モータを初期化する()
void CalibrationController::SensorMotorinit(){
	mGyroSensor.reset();
	mLeftMotor.reset();
	mRightMotor.reset();
	mTailMotor.reset();
}
