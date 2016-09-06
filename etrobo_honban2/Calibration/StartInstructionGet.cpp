//スタート指示取得
#include "StartInstructionGet.h"

StartInstructionGet::StartInstructionGet(UIGet* uiget)
	:mUIGet(uiget){
}

//メソッド： bool スタート指示を取得する（）
bool StartInstructionGet::StartInstructionGetter(){

	bool result = false;

	//Bluetooth or タッチセンサー指示があればtrueを返す
//	if (mUIGet -> UIGetter().touch || mUIGet -> UIGetter().btc == '1') {

	UI ui	= mUIGet->UIGetter();

	if (ui.touch || ui.btcKey == '1'){
		result = true;
	}

//	if (ui.touch)	return	true;
//
//	if (ui.btcKey == '1')	return	true;
//
//	if(ui.btcKey >= '0')	return	true;


	return result;
}

