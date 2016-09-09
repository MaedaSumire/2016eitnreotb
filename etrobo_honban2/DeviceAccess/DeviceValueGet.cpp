//デバイス値取得
#include "DeviceValueGet.h"

DeviceValueGet::DeviceValueGet( DeviceInterface* pDeviceInterface )
{
	m_pDeviceInterface	= pDeviceInterface;
}

//DV = DeviceValue
//メソッド: DV デバイス値を取得する() return DV(構造体)
DV DeviceValueGet::DeviceValueGetter(){
	DV dv;


	dv.sonar 		= m_pDeviceInterface->m_pCSonarSensor->getDistance();
	dv.color 		= m_pDeviceInterface->m_pCColorSensor->getBrightness();
	dv.gyro 		= m_pDeviceInterface->m_pCGyroSensor->getAnglerVelocity();
	dv.Lmotor_angle = m_pDeviceInterface->m_pCLeftMotor->getCount();
	dv.Rmotor_angle = m_pDeviceInterface->m_pCRightMotor->getCount();
	dv.Tmotor 		= m_pDeviceInterface->m_pCTailMotor->getCount();
	dv.GYRO_OFFSET 	= 0;
	dv.volt 		= m_pDeviceInterface->m_pCBattery->GetmV();
	dv.Lmotor_pwm = 0;
	dv.Rmotor_pwm = 0;

	return dv;

}
