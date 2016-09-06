//ユーザ操作取得
#include "UIGet.h"

UIGet::UIGet(ev3api::TouchSensor& touchsensor,
		StartInstructionGet* startinstructionget)
	:mTouchSensor(touchsensor),
	 mStartInstructionGet(startinstructionget){
}


//メソッド: UI ユーザ操作を取得する() return UI(構造体)
UI UIGet::UIGetter(){
	UI ui;
	ui.Button = 'N';
	ui.btc = 'p';
	ui.touch = false;
	int32_t bt_cmd = 0; /* Bluetoothコマンド 1:リモートスタート */

	if(ev3_button_is_pressed(BACK_BUTTON)){
		ui.Button = 'B';
	}
	else if(ev3_button_is_pressed(LEFT_BUTTON)){
		ui.Button = 'L';
	}
	else if(ev3_button_is_pressed(RIGHT_BUTTON)){
		ui.Button = 'R';
	}
	else if(ev3_button_is_pressed(UP_BUTTON)){
		ui.Button = 'U';
	}
	else if(ev3_button_is_pressed(DOWN_BUTTON)){
		ui.Button = 'D';
	}
	else if(ev3_button_is_pressed(ENTER_BUTTON)){
		ui.Button = 'E';
	}
	else if(mTouchSensor.isPressed()){
		ui.touch = true;
	}

	return ui;
}

