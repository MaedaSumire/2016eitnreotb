#include "DeviceValueGet.h"


DeviceValueGet::DeviceValueGet(ev3api::TouchSensor& touchSensor,
							   ev3api::SonarSensor& sonarSensor,
							   ev3api::ColorSensor& colorSensor,
							   ev3api::GyroSensor& gyroSensor,
							   ev3api::Motor& leftMotor,
							   ev3api::Motor& rightMotor,
							   ev3api::Motor& tailMotor)
		:mTouchSensor(touchSensor),
		 mSonarSensor(sonarSensor),
		 mColorSensor(colorSensor),
		 mGyroSensor(gyroSensor),
		 mLeftMotor(leftMotor),
		 mRightMotor(rightMotor),
		 mTailMotor(tailMotor){
}

int DeviceValueGetter(){
}
