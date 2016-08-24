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

bool DeviceValueGet::TouchSensorGetter(){
	return mTouchSensor->isPressed();
}

int16_t DeviceValueGet::SonarSensorGetter(){
	return mSonarSensor->getDistance();
}
int8_t DeviceValueGet::ColorSensorGetter(){
	return mColorSensor->getBrightness();
}

int16_t DeviceValueGet::GyroSensorGetter(){
	return mGyroSensor->getAngle();
}

int32_t DeviceValueGet::LeftMotorGetter(){
	return mLeftMotor->getCount();
}

int32_t DeviceValueGet::RightMotorGetter(){
	return mRightMotor->getCount();
}

int32_t DeviceValueGet::TailMotorGetter(){
	return mTailMotor->getCount();
}
