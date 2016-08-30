//キャリブレーションコントローラ
#include "CalibrationController.h"

CalibrationController::CalibrationController(ev3api::GyroSensor& gyrosensor,
											ev3api::Motor& leftmotor,
											ev3api::Motor& rightmotor,
											ev3api::Motor& tailmotor,
											PostureAdjustment* postureadjustment,
											ColorGet* colorget)
	:mGyroSensor(gyrosensor),
	 mLeftMotor(leftmotor),
	 mRightMotor(rightmotor),
	 mTailMotor(tailmotor),
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

		//走行体ボタン上下・左右で姿勢調節・輝度取得を切り替える
		if(true){//姿勢調節　走行体上下ボタンで姿勢調整、真ん中ボタンでこのwhileに戻る
			mPostureAdjustment -> PostureAdjust();
		}
		else if(false){//輝度取得　走行体左右ボタンで輝度取得、真ん中ボタンでこのwhileに戻る
			cc = mColorGet -> ColorGetter();
		}
	}
}

//メソッド: void センサ・モータを初期化する()
void CalibrationController::SensorMotorinit(){
	mGyroSensor.reset();
	mLeftMotor.reset();
	mRightMotor.reset();
	mTailMotor.reset();
}
