//スタートコントローラ
#include "StartController.h"

StartController::StartController(StartInstructionGet* startinstructionget)
	:mStartInstructionGet(startinstructionget){
}

//メソッド： void スタート判断する（）
void StartController::StartDicision(){

	bool result = false;

	//スタート指示があるまでループ
	while(1){

		/*関数呼び出し*/
		result = mStartInstructionGet -> StartInstructionGetter();

		if(result){
			break;
		}

	}

}

