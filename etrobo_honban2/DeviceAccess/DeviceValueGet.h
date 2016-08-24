#ifndef EV3_APP_DEVICEVALUEGET_H_
#define EV3_APP_DEVICEVALUEGET_H_

#include "ev3api.h"
#include "TouchSensor.h"
#include "SonarSensor.h"
#include "ColorSensor.h"
#include "GyroSensor.h"
#include "Motor.h"


class DeviceValueGet {
public:
	DeviceValueGet(ev3api::TouchSensor& touchSensor,
				   ev3api::SonarSensor& sonarSensor,
				   ev3api::ColorSensor& colorSensor,
				   ev3api::GyroSensor& gyroSensor,
				   ev3api::Motor& leftMotor,
				   ev3api::Motor& rightMotor,
				   ev3api::Motor& tailMotor);
	
	int DeviceValueGetter(){

private:

};

#endif  // EV3_APP_DEVICEVALUEGET_H_
