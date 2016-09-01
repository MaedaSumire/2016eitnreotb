////////////////////////////////////////////////
// �f�o�C�X�C���^�[�t�F�C�X��`
////////////////////////////////////////////////
#ifndef DEVICE_INTERFACE_H_
#define DEVICE_INTERFACE_H_

#include "ev3api.h"
#include "TouchSensor.h"
#include "SonarSensor.h"
#include "ColorSensor.h"
#include "GyroSensor.h"
#include "Motor.h"
#include "Clock.h"

///////////////////////////////////////////
//	CwrTouchSensor	�^�b�`�Z���T�[ ���b�p�[�N���X
///////////////////////////////////////////
class	CwrTouchSensor : public ev3api::TouchSensor{
public:
	CwrTouchSensor( ePortS port );		// �R���X�g���N�^�[
	~CwrTouchSensor();	// �f�X�g�^�N�^�[
};

///////////////////////////////////////////
//	CwrSonarSensor	�\�i�[�Z���T�[ ���b�p�[�N���X
///////////////////////////////////////////
class	CwrSonarSensor : public ev3api::SonarSensor{
public:
	CwrSonarSensor( ePortS port );		// �R���X�g���N�^�[
	~CwrSonarSensor();	// �f�X�g�^�N�^�[
};

///////////////////////////////////////////
//	CwrColorSensor	�J���[�Z���T�[ ���b�p�[�N���X
///////////////////////////////////////////
class	CwrColorSensor : public ev3api::ColorSensor{
public:
	CwrColorSensor( ePortS port );		// �R���X�g���N�^�[
	~CwrColorSensor();	// �f�X�g�^�N�^�[
};

///////////////////////////////////////////
//	CwrGyroSensor	�W���C���Z���T�[ ���b�p�[�N���X
///////////////////////////////////////////
class	CwrGyroSensor : public ev3api::GyroSensor{
public:
	CwrGyroSensor( ePortS port );		// �R���X�g���N�^�[
	~CwrGyroSensor();	// �f�X�g�^�N�^�[
};

///////////////////////////////////////////
//	CwrMotor	���[�^�[ ���b�p�[�N���X
///////////////////////////////////////////
class	CwrMotor : public ev3api::Motor{
public:
	CwrMotor( ePortM port );		// �R���X�g���N�^�[
	~CwrMotor();		// �f�X�g�^�N�^�[
};

///////////////////////////////////////////
//	CwrWheelMotor	�ԗփ��[�^�[�N���X
///////////////////////////////////////////
class	CwrWheelMotor : public CwrMotor{
public:
	CwrWheelMotor( ePortM port );		// �R���X�g���N�^�[
	~CwrWheelMotor();		// �f�X�g�^�N�^�[
};

///////////////////////////////////////////
//	CwrTailMotor	�e�[�����[�^�[�N���X
///////////////////////////////////////////
class	CwrTailMotor : public CwrMotor{
public:
	CwrTailMotor( ePortM port );		// �R���X�g���N�^�[
	~CwrTailMotor();	// �f�X�g�^�N�^�[
};

///////////////////////////////////////////
//	CwrClock	�N���b�N�N���X
///////////////////////////////////////////
class	CwrClock : public ev3api::Clock{
public:
	CwrClock();		// �R���X�g���N�^�[
	~CwrClock();	// �f�X�g�^�N�^�[
};

///////////////////////////////////////////
//	CwrBattery	�o�b�e���[�N���X
///////////////////////////////////////////
class	CwrBattery{
public:
	CwrBattery();		// �R���X�g���N�^�[
	~CwrBattery();	// �f�X�g�^�N�^�[

public:
	int	GetmA();	// �o�b�e���̓d�����擾����D�imA�j
	int	GetmV();	// �o�b�e���̓d�����擾����D�imV�j
};

///////////////////////////////////////////
//	CwrLEDLight	LED�N���X
///////////////////////////////////////////
class	CwrLEDLight{
public:
	CwrLEDLight();		// �R���X�g���N�^�[
	~CwrLEDLight();	// �f�X�g�^�N�^�[

public:
	ER	SetColor( ledcolor_t	color );	// LED���C�g�̃J���[��ݒ肷��
};

///////////////////////////////////////////
//	CwrSpeaker	�X�s�[�J�[�N���X
///////////////////////////////////////////
class	CwrSpeaker{
public:
	CwrSpeaker();		// �R���X�g���N�^�[
	~CwrSpeaker();	// �f�X�g�^�N�^�[

public:
	ER 	SetVolume(uint8_t nVolume);	// ���ʂ𒲐�����D
	ER 	PlayTone(					// �w�肵�����g���Ńg�[���o�͂���D���Đ����Ă���T�E���h�͒�~�����
					uint16_t nFrequency,	// �g�[���̎��g��
					int32_t nDuration		// �o�͎������ԁD�P�ʁF�~���b�DSOUND_MANUAL_STOP���w�肵���ꍇ�͎蓮�Œ�~����D
					);
	ER 	PlayFile(					// �w�肵��WAV�t�@�C���i8-bit 8kHz mono�j���Đ�����D
					const memfile_t *p_memfile,	// WAV�t�@�C���̃������t�@�C���ւ̃|�C���^
					int32_t nDuration			// �o�͎������ԁD�P�ʁF�~���b�DSOUND_MANUAL_STOP���w�肵���ꍇ�͎蓮�Œ�~���Ȃ��ƍŌ�܂ōĐ�����D
					);
	ER 	Stop();						// ���Đ����Ă���T�E���h���~����D [�ډ�]
};

///////////////////////////////////////////
//	CDeviceInterface	�f�o�C�X�C���^�[�t�F�C�X�N���X
///////////////////////////////////////////
class	CDeviceInterface{
public:
	CDeviceInterface();		// �R���X�g���N�^�[
	~CDeviceInterface();	// �f�X�g�^�N�^�[

public:
	CwrTouchSensor*	m_pCTouchSensor;	// �^�b�`�Z���T�[
	CwrSonarSensor*	m_pCSonarSensor;	// �\�i�[�Z���T�[
	CwrColorSensor*	m_pCColorSensor;	// �J���[�Z���T�[
	CwrGyroSensor*	m_pCGyroSensor;		// �W���C���Z���T�[
	CwrWheelMotor*	m_pCLeftMotor;		// �ԗփ��[�^�[ L
	CwrWheelMotor*	m_pCRightMotor;		// �ԗփ��[�^�[ R
	CwrTailMotor*	m_pCTailMotor;		// �e�[�����[�^�[
	CwrClock*		m_pCClock;			// �N���b�N

	CwrBattery*		m_pCBattery;		// �o�b�e���[�N���X
	CwrLEDLight*	m_pCLEDLight;		// LED�N���X
	CwrSpeaker*		m_pCSpeaker;		// �X�s�[�J�[�N���X
};
#endif  // DEVICE_INTERFACE_H_
