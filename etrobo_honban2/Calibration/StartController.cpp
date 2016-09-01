//スタートコントローラ
#include "StartController.h"

StartController::StartController(StartInstructionGet* startinstructionget,
		PostureAdjustment* postureadjustment,
		ev3api::Clock& clock)
	:mStartInstructionGet(startinstructionget),
	 mPostureAdjustment(postureadjustment),
	 mClock(clock){
}

//メソッド： void スタート判断する（）
void StartController::StartDicision(){

	bool result = false;

	//画面出力（削除可）
	ev3_lcd_draw_string("taiki_start", 0, 30);

	//スタート指示があるまでループ
	while(1){

		//しっぽ調整機能
		mPostureAdjustment -> PostureAdjust();

		//スタート指示の有無を受け取る
		result = mStartInstructionGet -> StartInstructionGetter();

		//スタート指示があればbreak
		if(result){
			break;
		}

		mClock.sleep(10);

	}

	//画面出力（削除可）
	ev3_lcd_draw_string("taiki_end", 0, 40);

}

