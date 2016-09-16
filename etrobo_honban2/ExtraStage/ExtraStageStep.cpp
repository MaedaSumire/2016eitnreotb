//階段攻略
#include "ExtraStageStep.h"

ExtraStageStep::ExtraStageStep(DeviceInterface* deviceinterface, UIGet* UiGet,
		CalibrationController* gCalibrationController) {

	m_pDeviceInterface = deviceinterface;
	m_pDeviceValueGet = new DeviceValueGet(deviceinterface);
	m_pMotorDrive = new MotorDrive(deviceinterface);
	m_pRunningCalculation = new RunningCalculation();
	m_pUIGet = UiGet;
	m_pCalibrationController = gCalibrationController;

}

extern int gCourse;

//メソッド：void 難所を攻略する（）
void ExtraStageStep::ExtraRun() {
	CALIBRAT calib = m_pCalibrationController->GetValue();
	float fTailSabun = calib.TailAngleStandUp - 93.0;

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
	int tempRmotor = 0;
	int tempTime2 = 0;

	tempTime2 = m_pDeviceInterface->m_pCClock->now();

	while (1) {
		//毎回しっぽモータに指示を出す
		m_pMotorDrive->TailMotorDrive(tail);
		dv_old = dv_now;
		dv_now = m_pDeviceValueGet->DeviceValueGetter();
		//dv_now.volt = 8000;

		// 1段目と衝突検知するまで、倒立させたまま速度10で走らせる
		if (now_section == 0) {
			dv_now = m_pRunningCalculation->RunningCalculate(dv_now,
					now_section);
			// 衝突検知したら区間を切り替える
			if (150 < dv_now.gyro
					&& m_pDeviceInterface->m_pCClock->now() - tempTime2
							> 3000) {
				tempRmotor = dv_now.Rmotor_angle; //左モータの回転数を取得しておく。
				now_section = 1;
			}
		}

		// 衝突後1段目上るまで、倒立させたまま速度10で走らせる
		else if (now_section == 1) {
			dv_now = m_pRunningCalculation->RunningCalculate(dv_now,
					now_section);
			// 左モータが一定角度回転したら次の区間へ
			if (dv_now.Rmotor_angle - tempRmotor > 120) {
				colisionTime = m_pDeviceInterface->m_pCClock->now(); //現在時刻を取得しておく。
				now_section = 2;
			}
		}

		// 1段目で停止
		else if (now_section == 2) {
			// 機体のバランスをとるため、一定時間速度10で倒立走行
			dv_now = m_pRunningCalculation->RunningCalculate(dv_now,
					now_section);
			tail = 80; //後ろに倒れるためしっぽ角度を調整
			//一定時間経過したら次の区間へ
			if (m_pDeviceInterface->m_pCClock->now() - colisionTime > 1500) {
				tempTime = m_pDeviceInterface->m_pCClock->now();  //現在時刻を取得しておく。
				now_section = 3;
			}
		}

		//　車輪の回転から1段目のどこにいるか推測し、位置を調整する。
		else if (now_section == 3) {
			tail = 75;
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
				if (dv_now.Rmotor_angle - tempRmotor > 300) {
					dv_now.Lmotor_pwm = -3;
					dv_now.Rmotor_pwm = -3;
				} else { //位置調整できたら区間を切り替える
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
				tempRmotor = dv_now.Rmotor_angle;
				now_section = 5;
			}
			dv_now.Lmotor_pwm = 15;
			dv_now.Rmotor_pwm = -15;
		}

		// 2点倒立開始
		else if (now_section == 5) {
			// 500msごとに尻尾角度を0.5上げる(=スタート待機時の姿勢に近づく)
			if (dv_now.Rmotor_angle - tempRmotor < 70) {
				dv_now.Lmotor_pwm = 3;
				dv_now.Rmotor_pwm = 3;
			} else {

				if (m_pDeviceInterface->m_pCClock->now() - tempTime > 500) {
					tail += 0.5;
					tempTime = m_pDeviceInterface->m_pCClock->now();
				}
				if (tail >= calib.TailAngleStandUp - 1) {
					tail = 80;
					tempTime = m_pDeviceInterface->m_pCClock->now();
					now_section = 6;
				}
			}
		}

		//2段目衝突検知するまで
		else if (now_section == 6) {
			//倒立後数秒間倒立
			if (m_pDeviceInterface->m_pCClock->now() - tempTime < 2000) {
				//PID,forwardすべて0にしたいので、now_section 3 のパラメータを借りています
				dv_now = m_pRunningCalculation->RunningCalculate(dv_now, 2);
			} else {
				dv_now = m_pRunningCalculation->RunningCalculate(dv_now,
						now_section);
				// 衝突検知
				if (150 < dv_now.gyro
						&& m_pDeviceInterface->m_pCClock->now() - tempTime
								> 4000) {
					tempRmotor = dv_now.Rmotor_angle;
					colisionTime = m_pDeviceInterface->m_pCClock->now();
					now_section = 7;
					ev3_lcd_draw_string("!!!collision!!!", 0, 70);
				}
			}
		}

		// 2段目に上る
		else if (now_section == 7) {
			dv_now = m_pRunningCalculation->RunningCalculate(dv_now,
					now_section);

			// 左モータが一定角度回転したら次の区間へ           //↓100で成功
			if (dv_now.Rmotor_angle - tempRmotor > 90) {
				colisionTime = m_pDeviceInterface->m_pCClock->now();
				now_section = 8;
			}
		}

		// 2段目で停止
		else if (now_section == 8) {

			dv_now = m_pRunningCalculation->RunningCalculate(dv_now,
					now_section);
			tail = 75;
			//↓500で成功
			if (m_pDeviceInterface->m_pCClock->now() - colisionTime > 1000) {
				tempTime = m_pDeviceInterface->m_pCClock->now();
				now_section = 9;
			}
		}

		// 位置調整
		else if (now_section == 9) {
			if (m_pDeviceInterface->m_pCClock->now() - tempTime < 300) {
				dv_now.GYRO_OFFSET = -5;
				dv_now = m_pRunningCalculation->RunningCalculate(dv_now,
						now_section);
			} else if (m_pDeviceInterface->m_pCClock->now() - tempTime > 1000) {
				if (dv_now.Rmotor_angle - tempRmotor > 300) {
					dv_now.Lmotor_pwm = -3;
					dv_now.Rmotor_pwm = -3;
				} else {
					turn = dv_now.Lmotor_angle;
					now_section = 10;
				}
			}
		}
		//回転
		else if (now_section == 10) {
			// モータ回転量が750を超えたら次の区間へ
			if (dv_now.Lmotor_angle - turn > 750) {
				dv_now.GYRO_OFFSET = 0;
				upStairTime = m_pDeviceInterface->m_pCClock->now();
				tempTime = m_pDeviceInterface->m_pCClock->now();
				tempRmotor = dv_now.Rmotor_angle;
				now_section = 11;
			}
			dv_now.Lmotor_pwm = 15;
			dv_now.Rmotor_pwm = -15;
		}
		// 2点倒立開始
		else if (now_section == 11) {
			if (dv_now.Rmotor_angle - tempRmotor < 70) {
				dv_now.Lmotor_pwm = 3;
				dv_now.Rmotor_pwm = 3;
			} else {

				if (m_pDeviceInterface->m_pCClock->now() - tempTime > 500) {
					tail += 0.5;
					tempTime = m_pDeviceInterface->m_pCClock->now();
				}
				if (tail >= calib.TailAngleStandUp - 1) {
					tail = 80;
					tempTime = m_pDeviceInterface->m_pCClock->now();
					now_section = 12;
				}
			}
		}
		//2段目降りたことを検知するまで
		else if (now_section == 12) {
			//倒立後数秒間倒立
			tail = 3;
			if (m_pDeviceInterface->m_pCClock->now() - tempTime < 2000) {
				//PID,forwardすべて0にしたいので、now_section 2 のパラメータを借りています
				dv_now = m_pRunningCalculation->RunningCalculate(dv_now, 2);
			} else {
				dv_now = m_pRunningCalculation->RunningCalculate(dv_now,
						now_section);
				//降りたことの検知
				if (150 < dv_now.gyro
						&& m_pDeviceInterface->m_pCClock->now() - tempTime
								> 4000) {
					tempRmotor = dv_now.Rmotor_angle;
					colisionTime = m_pDeviceInterface->m_pCClock->now();
					now_section = 13;
				}
			}
		}

		//降りて数秒その場で直立後、ライントレースする
		else if (now_section == 13) {
			tail = 3;

			if (m_pDeviceInterface->m_pCClock->now() - colisionTime < 2000)
				dv_now = m_pRunningCalculation->RunningCalculate(dv_now, 3);
			else {
				dv_now = m_pRunningCalculation->RunningCalculate(dv_now,
						now_section);
			}
		}

		m_pMotorDrive->LRMotorDrive(dv_now.Lmotor_pwm, dv_now.Rmotor_pwm);

		//ログ出力
		char* cLogBuff = m_pUIGet->GetBlueT()->pcLogBuff;
		sprintf(cLogBuff, "%lu,%d,%d,%d\n",
				m_pDeviceInterface->m_pCClock->now(), dv_now.color, dv_now.gyro,
				dv_now.volt);
		m_pUIGet->WriteLog(cLogBuff);

		m_pDeviceInterface->m_pCClock->sleep(3); /* 4msec周期起動 */

	}

	/*ガレージイン！*/

}
