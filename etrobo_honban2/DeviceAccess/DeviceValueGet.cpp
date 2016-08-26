#include "DeviceValueGet.h"


DeviceValueGet::DeviceValueGet(ev3api::TouchSensor* touchSensor,
							   ev3api::SonarSensor* sonarSensor,
							   ev3api::ColorSensor* colorSensor,
							   ev3api::GyroSensor* gyroSensor,
							   ev3api::Motor* leftMotor,
							   ev3api::Motor* rightMotor,
							   ev3api::Motor* tailMotor)
		:mTouchSensor(touchSensor),
		 mSonarSensor(sonarSensor),
		 mColorSensor(colorSensor),
		 mGyroSensor(gyroSensor),
		 mLeftMotor(leftMotor),
		 mRightMotor(rightMotor),
		 mTailMotor(tailMotor){
}

DeviceValue DeviceValueGet::DeviceValueGetter(){
	DeviceValue DV;

	DV.touch = mTouchSensor->isPressed();
	DV.sonar = mSonarSensor->getDistance();
	DV.color = mColorSensor->getBrightness();
	DV.gyro = mGyroSensor->getAnglerVelocity();
	DV.Lmotor_angle = mLeftMotor->getCount();
	DV.Rmotor_angle = mRightMotor->getCount();
	DV.Tmotor = mTailMotor->getCount();
	DV.GYRO_OFFSET = 0;
	DV.volt = ev3_battery_voltage_mV();
	DV.Lmotor_pwm;
	DV.Rmotor_pwm;

	return DV;

}
