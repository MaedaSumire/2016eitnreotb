#ifndef EXTRASTAGELOOKUP_H_
#define EXTRASTAGELOOKUP_H_

#include "ev3api.h"
#include "DeviceInterface.h"
#include "DeviceValueGet.h"
#include "MotorDrive.h"

class ExtraStageLookUp {
public:

	ExtraStageLookUp(DeviceInterface* m_pDeviceInterface);
	void ExtraRun();

private:

	DeviceInterface* 	m_pDeviceInterface;
	DeviceValueGet*		m_pDeviceValueGet;
	MotorDrive*			m_pMotorDrive;

};

#endif  // EXTRASTAGELOOKUP_H_
