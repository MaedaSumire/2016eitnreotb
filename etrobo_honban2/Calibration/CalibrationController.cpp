//キャリブレーションコントローラ
#include "CalibrationController.h"

CalibrationController::CalibrationController(ev3api::GyroSensor& gyrosensor,
											ev3api::Clock& clock,
											MotorDrive* motordrive,
											DeviceValueGet* deviceValueGet,
											UIGet* uiget)
	:mGyroSensor(gyrosensor),
	 mClock(clock),
	 mMotorDrive(motordrive),
	 mDeviceValueGet(deviceValueGet),
	 mUIGet(uiget)
{
	mCalibrat.White	= 34;	// 補正値 初期値
	mCalibrat.Black	= 1;	// 補正値 初期値
	mCalibrat.Half	= 22;	// 補正値 初期値
	mCalibrat.TailAngleStandUp	= 93.0;	// 直立時尻尾角度
}

//グローバル変数　LコースかRコースかを格納
int gCourse;

//メソッド： void キャリブレーションする（）
void CalibrationController::Calibrate(){
	UI	ui;
	DV	dv;

	//センサ・モータを初期化する
	SensorMotorinit();

	//画面表示
	Disp();

	while(1){
		ev3_lcd_draw_string("LCourse '<' or RCourse '>'", 0, 0);
		ui	= mUIGet->UIGetter();	// ループ１回につきUIGetterは１回にしないと取得できない
		if( ui.Button == 'L'){// EV3 Left_BUTTON押下
			gCourse = 1;
			ev3_lcd_draw_string("LCourse", 0, 10);
			break;
		}
		else if( ui.Button == 'R' ){// EV3 Right_BUTTON押下
			gCourse = 2;
			ev3_lcd_draw_string("RCourse", 0, 10);
			break;
		}
	}

	//画面出力（削除可）
	ev3_lcd_draw_string("calibration_start", 0, 20);

	//終了条件に達するまで姿勢調節・輝度取得を実施
	while(1){
		ui	= mUIGet->UIGetter();	// ループ１回につきUIGetterは１回にしないと取得できない

		if( ui.Button == 'E' )	break; // EV3 ENTER_BUTTON 押下

		if( ui.btcKey >= '0' ){
			dv	= mDeviceValueGet->DeviceValueGetter();		// デバイス値取得
			if		( ui.btcKey == 'w' || ui.btcKey == 'W' ){	// 白
				mCalibrat.White	= dv.color;
			}else if( ui.btcKey == 'b' || ui.btcKey == 'B' ){	// 黒
				mCalibrat.Black	= dv.color;
			}else if( ui.btcKey == 'h' || ui.btcKey == 'H' ){	// 中間値
				mCalibrat.Half	= dv.color;
			}
			Disp();
		}

		/*しっぽ角度調整*/
		if ( ui.Button == 'U' ){
			mCalibrat.TailAngleStandUp += 0.05;
		}
		else if (ui.Button == 'D'){
			mCalibrat.TailAngleStandUp -= 0.05;
		}
		mMotorDrive->TailMotorDrive(mCalibrat.TailAngleStandUp);

		mClock.sleep(10);
	}
	//画面出力（削除可）
	ev3_lcd_draw_string("calibration_end", 0, 30);

}

//メソッド: void センサ・モータを初期化する()
void CalibrationController::SensorMotorinit(){
	mGyroSensor.reset();
	mMotorDrive->reset();
}

// キャリブレーション値取得
CALIBRAT&	CalibrationController::GetValue()	// 値取得
{
	return	mCalibrat;
}

// キャリブレーション値設定
void		CalibrationController::SetValue(CALIBRAT& value)	// 値設定
{
	mCalibrat	= value;
}
// キャリブレーション値表示
void	CalibrationController::Disp()
{
	//画面表示
	BLUET* pBt	= mUIGet->GetBlueT();	// ブルーツース
	char	sbuff[100];
	fputc( '\n', pBt->pBtFile );
	sprintf(sbuff,"w : White =%d\n", mCalibrat.White);
	fputs( sbuff, pBt->pBtFile); 		// エコーバック
	sprintf(sbuff,"b : Black =%d\n", mCalibrat.Black);
	fputs( sbuff, pBt->pBtFile); 		// エコーバック
	sprintf(sbuff,"h : Half  =%d\n", mCalibrat.Half);
	fputs( sbuff, pBt->pBtFile); 		// エコーバック
}

