//競技走行
#include "ExtraStageStep.h"

ExtraStageStep::ExtraStageStep(DeviceInterface* deviceinterface){

	m_pDeviceInterface	= deviceinterface;
	m_pDeviceValueGet	= new	DeviceValueGet(deviceinterface);
	m_pMotorDrive = new MotorDrive(deviceinterface);
	m_pRunningCalculation = new RunningCalculation();
}

//メソッド：void 競技走行する（）
void ExtraStageStep::ExtraRun(){
	DV dv_old;
	DV dv_now = m_pDeviceValueGet -> DeviceValueGetter();
	//RD rd;
	double turn;
	double tail = 3;
	int count = 0;
	int now_section = 0;
	//int LMotorPWM;
	//int RMotorPWM;
	ev3_lcd_draw_string("Extra_start", 0, 80);

	while(1){
		/*ライントレースします*/
		m_pMotorDrive -> TailMotorDrive(tail);
		dv_old = dv_now;
		dv_now = m_pDeviceValueGet -> DeviceValueGetter();
		//dv_now.GYRO_OFFSET = -10;




		//turn = mPIDCalculation -> PIDCalculate(rd,dv_now.color);
		//balance_control((float)rd.forward, (float)turn, (float)dv_now.gyro,(float)dv_now.GYRO_OFFSET, (float)dv_now.Lmotor_angle,
		//(float)dv_now.Rmotor_angle, (float)dv_now.volt, (int8_t *)&dv_now.Lmotor_pwm, (int8_t *)&dv_now.Rmotor_pwm);
		//mMotorDrive -> LRMotorDrive(dv_now.Lmotor_pwm, dv_now.Rmotor_pwm);

		/*検知した輝度に従ってライントレースさせる場合*/
		//if(dv_now.color <= 3){ //黒の場合
		//	LMotorPWM = 40;
		//	RMotorPWM = 30;
		//}
		//else if(20 <= dv_now.color){ //白の場合
		//	LMotorPWM = 30;
		//	RMotorPWM = 40;
		//}
		//else{ //ほぼ境界の場合
		//	LMotorPWM = 40;
		//	RMotorPWM = 40;
		//}
		//
		//mMotorDrive -> LRMotorDrive(LMotorPWM,RMotorPWM);

		/*ぶつかりを判定します*/
		/*勢いをつけて上ります*/


		//800 < count && 30 < dv_now.gyro - dv_old.gyro
		if(now_section == 0 && 50 < dv_now.gyro - dv_old.gyro ){
			ev3_lcd_draw_string("!!collision!!", 0, 100);
			tail = 85;
			now_section = 1;
			count = 0;
		}
		else if(now_section == 0){
			/*倒立振子を使用したままライントレースさせる場合*/
			dv_now = m_pRunningCalculation->RunningCalculate(dv_now,now_section);
		}
		else if(now_section == 1 && count < 300){
			m_pMotorDrive -> LRMotorDrive(40,40);
		}
		else{
			m_pMotorDrive -> LRMotorDrive(0,0);
		}
//		else if(now_section == 1){
//
//		}



//		if(count = 10000){
//			while(1){
		//				dv_old = dv_now;
		//		dv_now = mDeviceValueGet -> DeviceValueGetter();
		//		dv_now = mRunningCalculation->RunningCalculate(dv_now,6);
		//		mMotorDrive -> LRMotorDrive(0,0);
		//	}

		//		}

		/*ライントレースし直します*/
		/*とまります*/
		/*回ります（多めに右回り）*/
		/*ラインに復帰します（黒が見つかるまで左回り）*/
		/*ライントレースし直します*/

		/*ぶつかりを判定します*/
		/*勢いをつけて上ります*/
		/*ライントレースし直します*/
		/*とまります*/
		/*回ります（多めに右回り）*/
		/*ラインに復帰します（黒が見つかるまで左回り）*/
		/*ライントレースし直します*/

		/*おります*/


		m_pMotorDrive -> LRMotorDrive(dv_now.Lmotor_pwm,dv_now.Rmotor_pwm);

		count ++;
		m_pDeviceInterface->m_pCClock->sleep(3); /* 4msec周期起動 */
	}

	/*ガレージイン！*/
}
