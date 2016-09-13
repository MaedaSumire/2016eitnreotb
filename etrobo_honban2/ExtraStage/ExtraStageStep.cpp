//競技走行
#include "ExtraStageStep.h"

ExtraStageStep::ExtraStageStep(DeviceInterface* deviceinterface, UIGet* UiGet) {

	m_pDeviceInterface = deviceinterface;
	m_pDeviceValueGet = new DeviceValueGet(deviceinterface);
	m_pMotorDrive = new MotorDrive(deviceinterface);
	m_pRunningCalculation = new RunningCalculation();
	m_pUIGet = UiGet;
}

extern int gCourse;

//メソッド：void 競技走行する（）
void ExtraStageStep::ExtraRun() {
	DV dv_old;
	DV dv_now = m_pDeviceValueGet->DeviceValueGetter();
	int32_t turn = 0;
	double tail = 10;
	int now_section = 0;
	gCourse = 3;	//　コース番号（3=階段）

	int colisionTime = 0;
	int upStairTime = 0;
	int turnTime = 0;
	int tempTime = 0;
	int tempLmotor = 0;

	while (1) {
		m_pMotorDrive->TailMotorDrive(tail);
		dv_old = dv_now;
		dv_now = m_pDeviceValueGet->DeviceValueGetter();

		// 1段目との衝突検知するまで
		if (now_section == 0) {
			dv_now = m_pRunningCalculation->RunningCalculate(dv_now,
					now_section);

			// 衝突検知
			if (150 < dv_now.gyro) {
				tempLmotor = dv_now.Lmotor_angle;
				now_section = 1;
			}

		}

		// 衝突後1段目上るまで
		else if (now_section == 1) {
			dv_now = m_pRunningCalculation->RunningCalculate(dv_now,
					now_section);

			// 左モータが一定角度回転したら次の区間へ
			if (dv_now.Lmotor_angle - tempLmotor > 100) {
				colisionTime = m_pDeviceInterface->m_pCClock->now();
				now_section = 2;
			}

		}

		// 1段目で停止
		else if (now_section == 2) {
			
			// 機体のバランスをとるため、一定時間速度0で倒立走行
			dv_now = m_pRunningCalculation->RunningCalculate(dv_now,
					now_section);
			tail = 80;
			
			if (m_pDeviceInterface->m_pCClock->now() - colisionTime > 1500) {
				tempTime = m_pDeviceInterface->m_pCClock->now();
				now_section = 3;
			}

		// 位置調整
		} else if (now_section == 3) {
			tail = 80;
			// 後ろ向きに下がりつつ、倒立走行する
			if (m_pDeviceInterface->m_pCClock->now() - tempTime < 300) {
				dv_now.GYRO_OFFSET = -5;
				dv_now = m_pRunningCalculation->RunningCalculate(dv_now,
						now_section);

			}
			
			// 300ms～1000msの間は停止
			
			
			else if (m_pDeviceInterface->m_pCClock->now() - tempTime > 1000) {
				// 前に進みすぎたら後ろに下がる
				// 特定位置より後ろに位置していたら前に進むロジックがあるとよりセーフティ
				if (dv_now.Lmotor_angle - tempLmotor > 300) {
					dv_now.Lmotor_pwm = -3;
					dv_now.Rmotor_pwm = -3;
				} else {
					turn = dv_now.Lmotor_angle;
					now_section = 4;
				}
			}
		}

		// 回転
		else if (now_section == 4) {
			// モータ回転量が750を超えたら次の区間へ
			if (dv_now.Lmotor_angle - turn > 750) {
				dv_now.GYRO_OFFSET = 0;
				upStairTime = m_pDeviceInterface->m_pCClock->now();
				tempTime = m_pDeviceInterface->m_pCClock->now();
				now_section = 5;
			}
			dv_now.Lmotor_pwm = 15;
			dv_now.Rmotor_pwm = -15;

		// 2点倒立開始
		} else if (now_section == 5) {
			dv_now.GYRO_OFFSET = 0;

			// 500msごとに尻尾角度を0.1上げる(=スタート待機時の姿勢に近づく)
			if (m_pDeviceInterface->m_pCClock->now() - tempTime > 500) {
				tail += 0.5;
				tempTime = m_pDeviceInterface->m_pCClock->now();
			}
			if (tail > 89) {
				tail = 89;
				tempTime = m_pDeviceInterface->m_pCClock->now();
				now_section = 6;
			}
		}

		//2段目衝突検知するまで
		else if (now_section == 6) {
			dv_now = m_pRunningCalculation->RunningCalculate(dv_now,
					now_section);

			// 衝突検知
			if (150 < dv_now.gyro && m_pDeviceInterface->m_pCClock->now() - tempTime > 1000) {
				tempLmotor = dv_now.Lmotor_angle;
				colisionTime = m_pDeviceInterface->m_pCClock->now();
				now_section = 7;
			}
		}

		// 2段目に上る
		else if (now_section == 7) {
			dv_now = m_pRunningCalculation->RunningCalculate(dv_now,
					now_section);

			// 左モータが一定角度回転したら次の区間へ
			if (dv_now.Lmotor_angle - tempLmotor > 1000) {
				colisionTime = m_pDeviceInterface->m_pCClock->now();
				now_section = 8;
			}
		}

		// 2段目で停止
		else if (now_section == 8) {

			dv_now = m_pRunningCalculation->RunningCalculate(dv_now,
					now_section);
			tail = 80;

			if (m_pDeviceInterface->m_pCClock->now() - colisionTime > 1500) {
				tempTime = m_pDeviceInterface->m_pCClock->now();
				now_section = 9;
			}
		}

		// 位置調整
		else if(now_section == 9) {
			if (m_pDeviceInterface->m_pCClock->now() - tempTime < 300) {
				dv_now.GYRO_OFFSET = -5;
				dv_now = m_pRunningCalculation->RunningCalculate(dv_now,
						now_section);

			} else if (m_pDeviceInterface->m_pCClock->now() - tempTime > 1000) {
				if (dv_now.Lmotor_angle - tempLmotor > 300) {
					dv_now.Lmotor_pwm = -3;
					dv_now.Rmotor_pwm = -3;
				} else {
					turn = dv_now.Lmotor_angle;
					now_section = 10;
				}
			}
		}

		else if (now_section == 10) {

			// モータ回転量が750を超えたら次の区間へ
			if (dv_now.Lmotor_angle - turn > 750) {
				dv_now.GYRO_OFFSET = 0;
				upStairTime = m_pDeviceInterface->m_pCClock->now();
				tempTime = m_pDeviceInterface->m_pCClock->now();
				now_section = 11;
			}
			dv_now.Lmotor_pwm = 15;
			dv_now.Rmotor_pwm = -15;
		}



		m_pMotorDrive->LRMotorDrive(dv_now.Lmotor_pwm, dv_now.Rmotor_pwm);

		//ログ出力
		char* cLogBuff = m_pUIGet->GetBlueT()->pcLogBuff;
		sprintf(cLogBuff, "%lu,%d,%d\n", m_pDeviceInterface->m_pCClock->now(),
				dv_now.color, dv_now.gyro);
		m_pUIGet->WriteLog(cLogBuff);

		m_pDeviceInterface->m_pCClock->sleep(3); /* 4msec周期起動 */

	}

	/*ガレージイン！*/
}
