#ifndef EXTRASTAGESTEP_H_
#define EXTRASTAGESTEP_H_

#include "ev3api.h"
#include "DeviceInterface.h"
#include "DeviceValueGet.h"
#include "MotorDrive.h"
#include "RunningCalculation.h"
#include "UIGet.h"

class ExtraStageStep {
public:

	ExtraStageStep(DeviceInterface* deviceinterface, UIGet* UiGet, CalibrationController* gCalibrationController);
	void ExtraRun();

private:

	DeviceInterface* 	m_pDeviceInterface;
	DeviceValueGet*		m_pDeviceValueGet;
	MotorDrive*			m_pMotorDrive;
	RunningCalculation* m_pRunningCalculation;
	UIGet*				m_pUIGet;
	CalibrationController*	m_pCalibrationController;

	float	m_fTailAngleStand;	// しっぽ立ち上がり

	// 指定距離移動
	void MoveDist(
			char	cLRsw,
			int		nDist,
			float	fTailAngle,
			int		nForward
			);

	// ポーズ
	void PauseEt(
			int		nTime,
			float	fTailAngle
			);

	// トレース計算する
	DV		CalcuTraceMoterPower(
			char	cLRsw,
			int		nForward
			);

	// オフセット付き角位置から距離に変換
	double	GetRunDistance(
			double	dMotorCount
			);

};

#endif  // EXTRASTAGESTEP_H_
