#ifndef STARTCONTROLLER_H_
#define STARTCONTROLLER_H_

#include "ev3api.h"
#include "Clock.h"
#include "CalibrationController.h"

class StartController {
public:

	StartController(
			DeviceInterface* 		pDeviceInterface,
			CalibrationController*	calibrationcontroller,
			UIGet* uiget
			);

	~StartController();

	void StartDicision();

private:
	DeviceInterface*		m_pDeviceInterface;
	CalibrationController*	m_pCalibrationController;
	UIGet* 					m_pUIGet;
	MotorDrive*				m_pMotorDrive;
};

#endif  // STARTCONTROLLER_H_
