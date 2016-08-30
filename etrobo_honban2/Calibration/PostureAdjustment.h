#ifndef POSTUREADJUSTMENT_H_
#define POSTUREADJUSTMENT_H_

#include "ev3api.h"
#include "DeviceValueGet.h"
#include "MotorDrive.h"

class PostureAdjustment {
public:

	PostureAdjustment(DeviceValueGet* devicevalueget, MotorDrive* motordrive);
	void PostureAdjust();

private:
	DeviceValueGet* mDeviceValueGet;
	MotorDrive* mMotorDrive;

};

#endif  // POSTUREADJUSTMENT_H_
