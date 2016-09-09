//白黒輝度取得
#include "ColorGet.h"

ColorGet::ColorGet(DeviceValueGet* devicevalueget)
	:mDeviceValueGet(devicevalueget){
}

//CC = CalibrationColor
//DV = DeviceValue
//メソッド： CC 輝度を取得する（）
CC ColorGet::ColorGetter(){

	CC cc;
	DV dv;

	/*カラー取得*/
	if(false){//bluetoothでキー入力があったら
		dv = mDeviceValueGet -> DeviceValueGetter();
		cc.white = dv.color;
	}
	else if(false){//bluetoothでキー入力があったら
		dv = mDeviceValueGet -> DeviceValueGetter();
		cc.black = dv.color;
	}


	return cc;
}

