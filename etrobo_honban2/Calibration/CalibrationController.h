#ifndef CALIBRATIONCONTROLLER_H_
#define CALIBRATIONCONTROLLER_H_

#include "ev3api.h"
#include "MotorDrive.h"
#include "GyroSensor.h"
#include "DeviceValueGet.h"
#include "Clock.h"
#include "UIGet.h"

typedef struct{		// �␳�l�\����
	int8_t	White;	// �P�x�@��
	int8_t	Black;	// �P�x�@��
	int8_t	Half;	// �P�x�@���Ԓl
	float	TailAngleStandUp;	// �������K���p�x
} CALIBRAT ;

class CalibrationController {
public:

	CalibrationController(ev3api::GyroSensor& gyrosensor,
							ev3api::Clock& clock,
							MotorDrive* motordrive,
							DeviceValueGet* deviceValueGet,
							UIGet* uiget);

	void RunningExecute(int now_section);
	void Calibrate();

	CALIBRAT&	GetValue();					// �l�擾
	void		SetValue(CALIBRAT& value);	// �l�ݒ�

private:
	void SensorMotorinit();

	ev3api::GyroSensor& mGyroSensor;
	ev3api::Clock& mClock;
	MotorDrive* mMotorDrive;
	DeviceValueGet* mDeviceValueGet;
	UIGet* mUIGet;

	CALIBRAT	mCalibrat;	// �␳�l

	// �L�����u���[�V�����l�\��
	void	Disp();

};

#endif  // CALIBRATIONCONTROLLER_H_
