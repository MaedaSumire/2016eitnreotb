#ifndef CALIBRATIONCONTROLLER_H_
#define CALIBRATIONCONTROLLER_H_

#include "ev3api.h"
//#include "Motor.h"
#include "MotorDrive.h"
#include "GyroSensor.h"
//#include "PostureAdjustment.h"
//#include "ColorGet.h"
#include "DeviceValueGet.h"
#include "Clock.h"
#include "UIGet.h"

typedef struct{		// 補正値構造体
	int8_t	White;	// 輝度　白
	int8_t	Black;	// 輝度　黒
	int8_t	Half;	// 輝度　中間値
	float	TailAngleStandUp;	// 直立時尻尾角度
} CALIBRAT ;

class CalibrationController {
public:

//	CalibrationController(ev3api::GyroSensor& gyrosensor, ev3api::Motor& leftmotor,
//							ev3api::Motor& rightmotor, ev3api::Motor& tailmotor,
//							ev3api::Clock& clock, PostureAdjustment* postureadjustment,
//							ColorGet* colorget, UIGet* uiget);
	CalibrationController(ev3api::GyroSensor& gyrosensor,
							ev3api::Clock& clock,
							MotorDrive* motordrive,
							DeviceValueGet* deviceValueGet,
							UIGet* uiget);

	void RunningExecute(int now_section);
	void Calibrate();

	CALIBRAT&	GetValue();					// 値取得
	void		SetValue(CALIBRAT& value);	// 値設定

private:
	void SensorMotorinit();

	ev3api::GyroSensor& mGyroSensor;
//	ev3api::Motor& mLeftMotor;
//	ev3api::Motor& mRightMotor;
//	ev3api::Motor& mTailMotor;
	ev3api::Clock& mClock;
	MotorDrive* mMotorDrive;
//	PostureAdjustment* mPostureAdjustment;
//	ColorGet* mColorGet;
	DeviceValueGet* mDeviceValueGet;
	UIGet* mUIGet;

	CALIBRAT	mCalibrat;	// 補正値

	// キャリブレーション値表示
	void	Disp();

};

#endif  // CALIBRATIONCONTROLLER_H_
