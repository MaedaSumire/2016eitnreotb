#ifndef EV3_APP_DEVICEVALUEGET_H_
#define EV3_APP_DEVICEVALUEGET_H_

#include "ev3api.h"
#include "TouchSensor.h"
#include "SonarSensor.h"
#include "ColorSensor.h"
#include "GyroSensor.h"
#include "Motor.h"

typedef struct{
	bool touch;
	int16_t sonar;
	int8_t color;
	int16_t gyro;
	int32_t Lmotor_angle;
	int32_t Rmotor_angle;
	int32_t Tmotor;
	int GYRO_OFFSET = 0;
	int32_t volt;
<<<<<<< HEAD
	signed char Lmotor_pwm;
	signed char Rmotor_pwm;
=======
	int8_t Lmotor_pwm;
	int8_t Rmotor_pwm;
>>>>>>> remotes/origin/maeda
} DeviceValue ;

class DeviceValueGet {
public:
	DeviceValueGet(ev3api::TouchSensor* touchSensor,
				   ev3api::SonarSensor* sonarSensor,
				   ev3api::ColorSensor* colorSensor,
				   ev3api::GyroSensor* gyroSensor,
				   ev3api::Motor* leftMotor,
				   ev3api::Motor* rightMotor,
				   ev3api::Motor* tailMotor);
	DeviceValue DeviceValueGetter();

private:
		ev3api::TouchSensor* mTouchSensor;
		ev3api::SonarSensor* mSonarSensor;
		ev3api::ColorSensor* mColorSensor;
		ev3api::GyroSensor* mGyroSensor;
		ev3api::Motor* mLeftMotor;
		ev3api::Motor* mRightMotor;
		ev3api::Motor* mTailMotor;
};

#endif  // EV3_APP_DEVICEVALUEGET_H_
