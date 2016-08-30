//姿勢調節
#include "PostureAdjustment.h"

PostureAdjustment::PostureAdjustment(DeviceValueGet* devicevalueget,
									MotorDrive* motordrive)
	:mDeviceValueGet(devicevalueget),
	 mMotorDrive(motordrive){
}

//メソッド： void しっぽモータの角度を調節する（）
void PostureAdjustment::PostureAdjust(){

	//真ん中ボタンが押されたら抜ける
	while(1){

		/*しっぽ角度調整*/


		if(true){
			break;
		}

	}
}

