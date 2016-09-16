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

	uint32_t			m_uStartTime;	// �J�n����
	uint32_t			m_uNowTime;		// ���ݎ���
	uint32_t			m_uElapsedTime; // �o�ߎ���

	float	m_fTailAngleStand;	// �����ۗ����オ��
	float	m_fTailAngleStandLow;	// �����ۗ����オ��
	float	m_fTailAngleStandFine;	// �����ۗ����オ��


	float	m_fTailAngleSlant;	// �����ۃ����{�[
	int16_t	m_nDistanceMin;		// �\�i�[�Z���T�[����cm



	// �Q�[�g�ɍs��
	void GoGate(
				char	cLRsw,
				float	fTailAngle
			);

	//���s�̂������{�[
	float Limbo(
			char	cLRsw,
			float	fTailAngle
			);

	// �����ۂ𗧂Ă�
	float	StandUpTail(
			float	fTailAngle
			);

	// �����ۂ𗧂Ă�
	float	StandUpTailFine(
			float	fTailAngle
			);


	// �w�苗���ړ�
	void MoveDist(
			char	cLRsw,
			int		nDist,
			float	fTailAngle,
			int		nForward
			);

	// �X�s��
	void Spin(
			int nAng,
			float	fTailAngle
			);

	// �|�[�Y
	void PauseEt(
			int		nTime,
			float	fTailAngle
			);

	// �o�ߎ��Ԏ擾
	// m_uNowTime �� m_uElapsedTime��ݒ�
	uint32_t	GetElapsedTime();

	// �I�t�Z�b�g�t���p�ʒu���狗���ɕϊ�
	double	GetRunDistance(
			double	dMotorCount
			);

	// �L�[�{�[�h���͂ɂ��u���C�N�w��
	bool	IsKeyBreak(
			float	fTailAngle
			);

	// �g���[�X�v�Z����
	DV		CalcuTraceMoterPower(
			char	cLRsw,
			int		nForward
			);

	// �G���f�B���O
	void	Ending();

};

#endif  // EXTRASTAGELOOKUP_H_
