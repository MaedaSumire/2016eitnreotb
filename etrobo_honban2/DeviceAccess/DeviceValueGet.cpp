//デバイス値取得
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

//DV = DeviceValue
//メソッド: DV デバイス値を取得する() return DV(構造体)
DV DeviceValueGet::DeviceValueGetter(){
	DV dv;

	dv.touch = mTouchSensor.isPressed();
	dv.sonar = mSonarSensor.getDistance();
	dv.color = mColorSensor.getBrightness();
	dv.gyro = mGyroSensor.getAnglerVelocity();
	dv.Lmotor_angle = mLeftMotor.getCount();
	dv.Rmotor_angle = mRightMotor.getCount();
	dv.Tmotor = mTailMotor.getCount();
	dv.GYRO_OFFSET = 0;
	dv.volt = ev3_battery_voltage_mV();
	dv.Lmotor_pwm;
	dv.Rmotor_pwm;

	return dv;

}
