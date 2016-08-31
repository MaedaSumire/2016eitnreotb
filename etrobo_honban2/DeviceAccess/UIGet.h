#ifndef EV3_APP_UIGET_H_
#define EV3_APP_UIGET_H_

#include "ev3api.h"
#include "TouchSensor.h"

//Button -- Left, Right, Up, Down, Back, Enter, None
//btc -- bluetoothcommand (key)
//touvh -- TouchSensorisPressed TF
typedef struct{
	char Button;
	uint8_t btc;
	bool touch;
} UI ;

class UIGet {
public:
	UIGet(ev3api::TouchSensor& touchsensor);
	UI UIGetter();

private:
	ev3api::TouchSensor& mTouchSensor;
};

#endif  // EV3_APP_UIGET_H_
