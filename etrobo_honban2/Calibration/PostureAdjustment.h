#ifndef POSTUREADJUSTMENT_H_
#define POSTUREADJUSTMENT_H_

#include "ev3api.h"
#include "DeviceValueGet.h"
#include "MotorDrive.h"
#include "UIGet.h"

class PostureAdjustment {
public:

	PostureAdjustment(DeviceValueGet* devicevalueget, MotorDrive* motordrive,
						UIGet* uiget);
	void PostureAdjust();

private:
	DeviceValueGet* mDeviceValueGet;
	MotorDrive* mMotorDrive;
	UIGet* mUIGet;
	float TAIL_ANGLE_STAND_UP;

};

#endif  // POSTUREADJUSTMENT_H_
