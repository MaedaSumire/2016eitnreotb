#ifndef EXTRASTAGELOOKUP_H_
#define EXTRASTAGELOOKUP_H_

#include "ev3api.h"
#include "DeviceInterface.h"
#include "CalibrationController.h"
#include "DeviceValueGet.h"
#include "MotorDrive.h"
#include "UIGet.h"
#include "PIDCalculation.h"
#include "balancer.h"
#include "RunningData.h"

#include "RunningCalculation.h"

class ExtraStageLookUp {
public:

	ExtraStageLookUp(
			DeviceInterface* m_pDeviceInterface,
			UIGet* guiget,
			CalibrationController*	gCalibrationController
		);

	void ExtraRun();

private:

	DeviceInterface* 	m_pDeviceInterface;
	UIGet*				m_pUIGet;
	CalibrationController*	m_pCalibrationController;

	RunningCalculation* m_pRunningCalculation;

	DeviceValueGet*		m_pDeviceValueGet;
	MotorDrive*			m_pMotorDrive;

	PIDCalculation		mPIDCalculation;

	uint32_t			m_uStartTime;	// 開始時間
	uint32_t			m_uNowTime;		// 現在時間
	uint32_t			m_uElapsedTime; // 経過時間

	float	m_fTailAngleStand;	// しっぽ立ち上がり
	float	m_fTailAngleStand2;	// しっぽ立ち上がり
	float	m_fTailAngleStandLow;	// しっぽ立ち上がり
	float	m_fTailAngleStandFine;	// しっぽ立ち上がり


	float	m_fTailAngleSlant;	// しっぽリンボー
	int16_t	m_nDistanceMin;		// ソナーセンサー距離cm
	int		m_nFinalRunDist;	// ガレージまでの最終走行距離

	// ゲートに行く
	void GoGate(
				char	cLRsw,
				float	fTailAngle
			);

	//走行体をリンボー
	float Limbo(
			char	cLRsw,
			float	fTailAngle
			);

	// しっぽを立てる
	float	StandUpTail(
			float	fTailAngle
			);

	// しっぽを立てる
	float	StandUpTailFine(
			float	fTailAngle
			);


	// 指定距離移動
	void MoveDist(
			char	cLRsw,
			int		nDist,
			float	fTailAngle,
			int		nForward
			);

	// スピン
	void Spin(
			int nAng,
			float	fTailAngle
			);

	// ポーズ
	void PauseEt(
			int		nTime,
			float	fTailAngle
			);

	// 経過時間取得
	// m_uNowTime と m_uElapsedTimeを設定
	uint32_t	GetElapsedTime();

	// オフセット付き角位置から距離に変換
	double	GetRunDistance(
			double	dMotorCount
			);

	// キーボード入力によるブレイク指示
	bool	IsKeyBreak(
			float	fTailAngle
			);

	// トレース計算する
	DV		CalcuTraceMoterPower(
			char	cLRsw,
			int		nForward
			);

	// エンディング
	void	Ending();

};

#endif  // EXTRASTAGELOOKUP_H_
