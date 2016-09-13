// 未使用

#ifndef COLORGET_H_
#define COLORGET_H_

#include "ev3api.h"
#include "DeviceValueGet.h"

typedef struct{
	int8_t white;
	int8_t black;
}CC;

class ColorGet {
public:

	ColorGet(DeviceValueGet* devicevalueget);
	CC ColorGetter();

private:
	DeviceValueGet* mDeviceValueGet;

};

#endif  // COLORGET_H_
