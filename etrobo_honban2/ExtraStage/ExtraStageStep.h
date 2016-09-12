#ifndef EXTRASTAGESTEP_H_
#define EXTRASTAGESTEP_H_

#include "ev3api.h"
#include "DeviceInterface.h"
#include "DeviceValueGet.h"
#include "MotorDrive.h"
#include "RunningCalculation.h"
#include "UIGet.h"

class ExtraStageStep {
public:

	ExtraStageStep(DeviceInterface* deviceinterface, UIGet* UiGet);
	void ExtraRun();

private:

	DeviceInterface* 	m_pDeviceInterface;
	DeviceValueGet*		m_pDeviceValueGet;
	MotorDrive*			m_pMotorDrive;
	RunningCalculation* m_pRunningCalculation;
	UIGet*				m_pUIGet;

};

#endif  // EXTRASTAGESTEP_H_
