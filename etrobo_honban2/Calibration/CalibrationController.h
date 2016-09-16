#ifndef CALIBRATIONCONTROLLER_H_
#define CALIBRATIONCONTROLLER_H_

#include "ev3api.h"
#include "DeviceInterface.h"
#include "MotorDrive.h"
#include "GyroSensor.h"
#include "DeviceValueGet.h"
#include "Clock.h"
#include "UIGet.h"
#include "PIDCalculation.h"
#include "balancer.h"
#include "RunningDataGet.h"

typedef struct{		// 補正値構造体
	int8_t	White;	// 輝度　白
	int8_t	Black;	// 輝度　黒
	int8_t	Half;	// 輝度　中間値
	float	TailAngleStandUp;	// 直立時尻尾角度
	char	Running;	// 'c' : Conpetition & ExtraStage, 'x' ExtraStage Only
} CALIBRAT ;

class CalibrationController {
public:

	CalibrationController(DeviceInterface* pDeviceInterface,
							UIGet* uiget);

	~CalibrationController();

	void RunningExecute(int now_section);
	void Calibrate();

	CALIBRAT&	GetValue();				// 値取得
	void		SetValue(CALIBRAT& value);	// 値設定

private:

	DeviceInterface*	m_pDeviceInterface;
	UIGet* 				m_pUIGet;

	MotorDrive* m_pMotorDrive;
	DeviceValueGet* m_pDeviceValueGet;

	CALIBRAT	mCalibrat;	// 補正値

	void	SensorMotorinit();

	// キャリブレーション値表示
	void	Disp();

};

#endif  // CALIBRATIONCONTROLLER_H_
