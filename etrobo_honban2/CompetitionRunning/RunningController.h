#ifndef RUNNINGCONTROLLER_H_
#define RUNNINGCONTROLLER_H_

#include "ev3api.h"
#include "DeviceInterface.h"
#include "DeviceValueGet.h"
#include "RunningCalculation.h"
#include "UIGet.h"

class RunningController {
public:

	RunningController(
					DeviceInterface* deviceinterface,
					UIGet* uiget
					);

	~RunningController();

	void RunningExecute(int now_section);


private:
	DeviceInterface* m_pDeviceInterface;
	UIGet* m_pUIGet;


	DeviceValueGet*		m_pDeviceValueGet;
	RunningCalculation*	m_pRunningCalculation;
	MotorDrive*			m_pMotorDrive;

};

#endif  // RUNNINGCALCULATION_H_
