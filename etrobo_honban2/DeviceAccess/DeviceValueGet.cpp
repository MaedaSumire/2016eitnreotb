//デバイス値取得
#include "DeviceValueGet.h"


DeviceValueGet::DeviceValueGet(ev3api::SonarSensor& sonarsensor,
							   ev3api::ColorSensor& colorsensor,
							   ev3api::GyroSensor& gyrosensor,
							   ev3api::Motor& leftmotor,
							   ev3api::Motor& rightmotor,
							   ev3api::Motor& tailmotor)
		:mSonarSensor(sonarsensor),
		 mColorSensor(colorsensor),
		 mGyroSensor(gyrosensor),
		 mLeftMotor(leftmotor),
		 mRightMotor(rightmotor),
		 mTailMotor(tailmotor){
}

//DV = DeviceValue
//メソッド: DV デバイス値を取得する() return DV(構造体)
DV DeviceValueGet::DeviceValueGetter(){
	DV dv;

	dv.sonar = mSonarSensor.getDistance();
	dv.color = mColorSensor.getBrightness();
	dv.gyro = mGyroSensor.getAnglerVelocity();
	dv.Lmotor_angle = mLeftMotor.getCount();
	dv.Rmotor_angle = mRightMotor.getCount();
	dv.Tmotor = mTailMotor.getCount();
	dv.GYRO_OFFSET = 0;
	dv.volt = ev3_battery_voltage_mV();
	dv.Lmotor_pwm = 0;
	dv.Rmotor_pwm = 0;

	return dv;

}
