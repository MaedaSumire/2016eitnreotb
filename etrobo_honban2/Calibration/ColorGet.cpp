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

	//真ん中ボタンが押されたら抜ける
	while(1){

		/*カラー取得*/
		if(true){//bluetoothでキー入力があったら
			dv = mDeviceValueGet -> DeviceValueGetter();
			cc.white = dv.color;
		}
		else if(false){//bluetoothでキー入力があったら
			dv = mDeviceValueGet -> DeviceValueGetter();
			cc.black = dv.color;
		}

		if(true){//真ん中ボタンが押されたら抜ける
			break;
		}

	}

	return cc;
}

