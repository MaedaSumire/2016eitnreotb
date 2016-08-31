//姿勢調節
#include "PostureAdjustment.h"

PostureAdjustment::PostureAdjustment(DeviceValueGet* devicevalueget,
									MotorDrive* motordrive,
									UIGet* uiget)
	:mDeviceValueGet(devicevalueget),
	 mMotorDrive(motordrive),
	 mUIGet(uiget),
	 TAIL_ANGLE_STAND_UP(93){
}

//メソッド： void しっぽモータの角度を調節する（）
void PostureAdjustment::PostureAdjust(){

	char c;

	c = mUIGet -> UIGetter().Button;
	/*しっぽ角度調整*/
	if ( c == 'U' ){
		TAIL_ANGLE_STAND_UP = TAIL_ANGLE_STAND_UP + 0.1;
	}
	else if (c == 'D'){
		TAIL_ANGLE_STAND_UP = TAIL_ANGLE_STAND_UP - 0.1;
	}

	mMotorDrive -> TailMotorDrive(TAIL_ANGLE_STAND_UP);

}

