#ifndef MOTORDRIVE_H_
#define MOTORDRIVE_H_

#include "DeviceInterface.h"

class MotorDrive {
public:
	
	MotorDrive( DeviceInterface* pDeviceInterface );
	
	void LRMotorDrive(	int8_t leftPWM,
						int8_t rightPWM);
	void TailMotorDrive(float angle);
	
	void reset();

private:

	DeviceInterface* m_pDeviceInterface;
};

#endif  // MOTORDRIVE_H_
