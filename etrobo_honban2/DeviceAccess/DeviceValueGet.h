#ifndef EV3_APP_DEVICEVALUEGET_H_
#define EV3_APP_DEVICEVALUEGET_H_

#include "DeviceInterface.h"

typedef struct{
	int16_t sonar;
	int8_t color;
	int16_t gyro;
	int32_t Lmotor_angle;
	int32_t Rmotor_angle;
	int32_t Tmotor;
	int GYRO_OFFSET;
	int32_t volt;
	int8_t Lmotor_pwm = 0;
	int8_t Rmotor_pwm = 0;
} DV ;

class DeviceValueGet {
public:

	DeviceValueGet( DeviceInterface* pDeviceInterface );

	DV DeviceValueGetter();

private:

		DeviceInterface* m_pDeviceInterface;
};

#endif  // EV3_APP_DEVICEVALUEGET_H_
