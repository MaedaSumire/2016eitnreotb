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
	double tail = 3;
	int now_section = 0;
	gCourse = 3;	//　コース番号（3=階段）

	int colisionTime = 0;
	int upStairTime = 0;
	int turnTime = 0;

	while (1) {
		/*ライントレースします*/
		m_pMotorDrive->TailMotorDrive(tail);
		dv_old = dv_now;
		dv_now = m_pDeviceValueGet->DeviceValueGetter();

		// 衝突検知するまで
		if (now_section == 0) {
			dv_now = m_pRunningCalculation->RunningCalculate(dv_now,
					now_section);

			// 衝突検知
			if (100 < dv_now.gyro) {
				colisionTime = m_pDeviceInterface->m_pCClock->now();
				now_section = 1;
			}
		}

		// 衝突後1段目上がり、300ms経過するまで
		else if (now_section == 1) {
			dv_now = m_pRunningCalculation->RunningCalculate(dv_now,
					now_section);

			// 衝突から300ms秒後
			if (m_pDeviceInterface->m_pCClock->now() - colisionTime > 300) {
				upStairTime = m_pDeviceInterface->m_pCClock->now();
				now_section = 2;
			}
		}

		// 1段目で停止
		else if (now_section == 2) {
			dv_now = m_pRunningCalculation->RunningCalculate(dv_now,
					now_section);
			tail = 80;
			dv_now.GYRO_OFFSET = -20;

			// 1段目上って2000ms経過したら次の区間へ
			if (m_pDeviceInterface->m_pCClock->now() - upStairTime > 2000) {
				turn = dv_now.Lmotor_angle;
				turnTime = m_pDeviceInterface->m_pCClock->now();
				now_section = 3;
			}

		// 倒立振子切り、3点倒立→3秒後に回転開始
		} else if (now_section == 3) {
			tail = 80;

			// 3点倒立開始して3秒が経過したら回転開始
			if (m_pDeviceInterface->m_pCClock->now() - turnTime > 3000) {

				// モータ回転量が750を超えたら次の区間へ
				if (dv_now.Lmotor_angle - turn > 750) {
					dv_now.GYRO_OFFSET = 0;
					upStairTime = m_pDeviceInterface->m_pCClock->now();
					now_section = 4;
				}
				dv_now.Lmotor_pwm = 15;
				dv_now.Rmotor_pwm = -15;
			}
			// 3点倒立開始して3秒未満はLRのモータへの出力なし
			else {
				dv_now.Lmotor_pwm = 0;
				dv_now.Rmotor_pwm = 0;
			}

		// あとはお願いします
		} else if (now_section == 4) {

		}

		m_pMotorDrive->LRMotorDrive(dv_now.Lmotor_pwm, dv_now.Rmotor_pwm);

		//ログ出力
		char* cLogBuff = m_pUIGet->GetBlueT()->pcLogBuff;
		sprintf(cLogBuff, "%lu,%d,%d,%d\n",
				m_pDeviceInterface->m_pCClock->now(), dv_now.Lmotor_angle,
				dv_now.Rmotor_angle,
				m_pDeviceInterface->m_pCClock->now() - turnTime);
		m_pUIGet->WriteLog(cLogBuff);

		m_pDeviceInterface->m_pCClock->sleep(3); /* 4msec周期起動 */

	}

	/*ガレージイン！*/
}
