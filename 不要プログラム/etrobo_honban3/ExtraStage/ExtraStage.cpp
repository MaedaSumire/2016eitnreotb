//競技走行
#include "ExtraStage.h"

ExtraStage::ExtraStage( MotorDrive* motordrive,
						DeviceValueGet* devicevalueget,
						ev3api::Clock& clock)
	:mMotorDrive(motordrive),
	 mDeviceValueGet(devicevalueget),
	 mClock(clock){
}

//メソッド：void 競技走行する（）
void ExtraStage::ExtraRun(){

	/*倒立振子が切れた状態からスタートです。始終倒立振子は切れています。*/

	float tailAngle = 85;
	int count = 0 ;
	int lmotor = 0;
	int rmotor = 0;
	DV dv;

	ev3_lcd_draw_string("Extra_start", 0, 80);

	while(1){
		//while文が回るたびにデバイス値取得としっぽ制御、モータ駆動とカウントアップを実行する
		//dv = mDeviceValueGet->DeviceValueGetter();
		mMotorDrive->TailMotorDrive(tailAngle);
		//mMotorDrive->LRMotorDrive(lmotor,rmotor);
		count++;

		if(0<= count && count < 10000){
			//走行体の加速と同時に尻尾をおろす
			lmotor = 40;
			rmotor = 40;
			ev3_lcd_draw_string("Extra_totyu1", 0, 0);
		}
		else if(10000 <= count  && count < 12000){
			//走行停止、徐々に尻尾を下げ、走行体を後傾させる
			lmotor = 0;
			rmotor = 0;
			if(count % 500 == 0){tailAngle = tailAngle - 5.0;}
			ev3_lcd_draw_string("Extra_totyu2", 0, 10);
		}
		else if(12000 <= count && count < 22000){
			//走行体を直進させる
			lmotor = 20;
			rmotor = 20;
			ev3_lcd_draw_string("Extra_totyu3", 0, 20);
		}
		else if(22000 <= count && count < 40000){
			//走行体を前後反転させる
			lmotor = 20;
			rmotor = -20;
			ev3_lcd_draw_string("Extra_totyu4", 0, 30);
		}
		else if(40000 <= count && count < 52000){
			//走行体を直進させる
			lmotor = 20;
			rmotor = 20;
			ev3_lcd_draw_string("Extra_totyu5", 0, 40);
		}
		else if(52000 <= count && count < 70000){
			//走行体を前後反転させる
			lmotor = 20;
			rmotor = -20;
			ev3_lcd_draw_string("Extra_totyu6", 0, 50);
		}
		else if(70000 <= count && count < 100000){
			//走行体を直進させる
			lmotor = 20;
			rmotor = 20;
			ev3_lcd_draw_string("Extra_totyu7", 0, 60);
		}
		//ガレージイン！
	}
}
