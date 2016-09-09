//競技走行
#include "ExtraStageStep.h"

ExtraStageStep::ExtraStageStep(DeviceInterface* deviceinterface) {

	m_pDeviceInterface = deviceinterface;
	m_pDeviceValueGet = new DeviceValueGet(deviceinterface);
	m_pMotorDrive = new MotorDrive(deviceinterface);
	m_pRunningCalculation = new RunningCalculation();
}

extern int gCourse;

//メソッド：void 競技走行する（）
void ExtraStageStep::ExtraRun() {
	DV dv_old;
	DV dv_now = m_pDeviceValueGet->DeviceValueGetter();
	//RD rd;
	double turn;
	double tail = 3;
	int now_section = 0;
	ev3_lcd_draw_string("Extra_start", 0, 80);
	gCourse = 3;
	uint8_t colisionTime = 0;
	uint8_t upStairTime = 0;

	while (1) {
		/*ライントレースします*/
		m_pMotorDrive->TailMotorDrive(tail);
		dv_old = dv_now;
		dv_now = m_pDeviceValueGet->DeviceValueGetter();
		//dv_now.GYRO_OFFSET = -10;

		// 衝突検知するまで(section=0)
		bool flag = false;
		if (now_section == 0) {


			dv_now = m_pRunningCalculation->RunningCalculate(dv_now,
					now_section);

			// 衝突検知
			if (50 < dv_now.gyro - dv_old.gyro && !(flag)) {
				ev3_lcd_draw_string("!!collision!!", 0, 100);
				colisionTime = m_pDeviceInterface->m_pCClock->now();
				flag = true;
			}

			// 衝突後1段目上がるまで
			if (flag
					&& m_pDeviceInterface->m_pCClock->now() - colisionTime
							> 2000) {
				upStairTime = m_pDeviceInterface->m_pCClock->now();
				now_section = 1;
			}
		}

		// 1段目で停止(section = 1)
		if (now_section == 1) {
			dv_now = m_pRunningCalculation->RunningCalculate(dv_now,
					now_section);
			tail = 85;
			dv_now.GYRO_OFFSET = -10;
			if (m_pDeviceInterface->m_pCClock->now() - upStairTime > 300) {
				now_section = 2;
			}
		}

		m_pMotorDrive->LRMotorDrive(dv_now.Lmotor_pwm, dv_now.Rmotor_pwm);

		m_pDeviceInterface->m_pCClock->sleep(3); /* 4msec周期起動 */
	}

	/*ガレージイン！*/
}
