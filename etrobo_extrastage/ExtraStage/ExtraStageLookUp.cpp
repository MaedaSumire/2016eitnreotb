//ルックアップゲート攻略
#include "ExtraStageLookUp.h"

ExtraStageLookUp::ExtraStageLookUp( MotorDrive* motordrive,
						DeviceValueGet* devicevalueget,
						ev3api::Clock& clock)
	:mMotorDrive(motordrive),
	 mDeviceValueGet(devicevalueget),
	 mClock(clock){
}

//メソッド：void 競技走行する（）
void ExtraStageLookUp::ExtraRun(){

	/*倒立振子が切れた状態からスタートです。始終倒立振子は切れています。*/

	//dv0:難所攻略開始のモーターカウントを保持
	//dv:モーターカウントを取得するための入れ物
	//count = dv.Rmotor_angle - dv0.Rmotor_angle
	DV dv0,dv;
	float tailAngle = 85;
	int count = 0 ;
	int lmotor = 0;
	int rmotor = 0;
	int section1 = 500; //走行体の加速と同時に尻尾をおろす
	int section2 = 15000; //走行停止、徐々に尻尾を下げ、走行体を後傾させる
	int section3 = 37000; //走行体を直進させる
	int section4 = 47000; //走行体を前後反転させる
	int section5 = 67000; //走行体を直進させる
	int section6 = 77000; //走行体を前後反転させる
	int section7 = 97000;//走行体を直進させる

	//デバイスの初期値を取ってくる
	dv0 = mDeviceValueGet->DeviceValueGetter();
	dv = dv0;

	ev3_lcd_draw_string("Extra_start", 0, 80);

	while(1){
		//while文が回るたびにデバイス値取得としっぽ制御、カウントアップを実行する
		mMotorDrive->TailMotorDrive(tailAngle);
		mMotorDrive->LRMotorDrive(lmotor,rmotor);
		count++;

		if(0<= count && count < section1){
			//走行体の加速と同時に尻尾をおろす
			lmotor = 40;
			rmotor = 40;
			ev3_lcd_draw_string("Extra_totyu1", 0, 0);
		}
		else if(section1 <= count  && count < section2){
			//走行停止、徐々に尻尾を下げ、走行体を後傾させる
			lmotor = 20;
			rmotor = 20;
			if(count % 100 == 0){tailAngle = tailAngle + 20;} //50度まで傾ける
			ev3_lcd_draw_string("Extra_totyu2", 0, 10);
		}
		else if(section2 <= count && count < section3){
			//走行体を直進させる
			lmotor = 20;
			rmotor = 20;
			ev3_lcd_draw_string("Extra_totyu3", 0, 20);
		}
		else if(section3 <= count && count < section4){
			//走行体を前後反転させる
			lmotor = 20;
			rmotor = -20;
			ev3_lcd_draw_string("Extra_totyu4", 0, 30);
		}
		else if(section4 <= count && count < section5){
			//走行体を直進させる
			lmotor = 20;
			rmotor = 20;
			ev3_lcd_draw_string("Extra_totyu5", 0, 40);
		}
		else if(section5 <= count && count < section6){
			//走行体を前後反転させる
			lmotor = 20;
			rmotor = -20;
			ev3_lcd_draw_string("Extra_totyu6", 0, 50);
		}
		else if(section6 <= count && count < section7){
			//走行体を直進させる
			lmotor = 20;
			rmotor = 20;
			ev3_lcd_draw_string("Extra_totyu7", 0, 60);
		}
		//ガレージイン！

		mClock.sleep(3); /* 4msec周期起動 */
	}
}
