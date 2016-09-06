//ユーザ操作取得
#include "UIGet.h"

// コンストラクター
UIGet::UIGet(ev3api::TouchSensor& touchsensor)
	:mTouchSensor(touchsensor){

	mLogBuff[0]	= 0;		// ログ出力用文字列バッファーポインター

	mBlueT.btcKey	= 0;// ブルーツース通信機器　キーボード入力
	mBlueT.pBtFile	= (FILE*)(0);		// ブルーツースFILEポインター
	mBlueT.pcLogBuff	= mLogBuff;		// ログ出力用文字列バッファーポインター
}

// ブルーツース構造体取得
BLUET*	UIGet::GetBlueT()
{
	return	&mBlueT;
}

// ブルーツースログ出力
void	UIGet::WriteLog(char* cBuff)	// ブルーツースログ出力
{
	fputs( cBuff, mBlueT.pBtFile );
}

//メソッド: UI ユーザ操作を取得する() return UI(構造体)
UI UIGet::UIGetter(){
	UI ui;
	ui.Button = 'N';
	ui.btcKey = 0;
	ui.touch = false;

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

	if(mBlueT.btcKey >= '0'){
		//　キーボード入力	app.c bt_task()にて取得される
		ui.btcKey	= mBlueT.btcKey;	// キー取得
		mBlueT.btcKey	= 0;			// キークリア

		char	sbuff[100];
		sprintf(sbuff,"test!! [%c]  \n",ui.btcKey);
		fputs( sbuff, mBlueT.pBtFile); 		// エコーバック
	}

//	if(*mpBtCmd >= '0'){
//		ui.btcKey = *mpBtCmd;
//		*mpBtCmd	= 0;	// キークリア
//	}

//	char	sbuff[100];
//	sprintf(sbuff,"test!! [%s]  \n",*mpBtCmd);
//	fputs( sbuff, mpBtFile); /* エコーバック */

//	ev3_lcd_draw_string(sbuff, 0, 30);

	return ui;
}
