////////////////////////////////////////////////
// �f�o�C�X�C���^�[�t�F�C�X��`
////////////////////////////////////////////////
#include "DeviceInterface.h"

/////////////////////
//	CDeviceInterface
/////////////////////
CDeviceInterface::CDeviceInterface()	// �R���X�g���N�^�[
{
	m_pCTouchSensor	= new CwrTouchSensor(PORT_1);	// �^�b�`�Z���T�[
	m_pCSonarSensor	= new CwrSonarSensor(PORT_2);	// �\�i�[�Z���T�[
	m_pCColorSensor	= new CwrColorSensor(PORT_3);	// �J���[�Z���T�[
	m_pCGyroSensor	= new CwrGyroSensor (PORT_4);	// �W���C���Z���T�[
	m_pCLeftMotor	= new CwrWheelMotor (PORT_C);	// �ԗփ��[�^�[ L
	m_pCRightMotor	= new CwrWheelMotor (PORT_B);	// �ԗփ��[�^�[ R
	m_pCTailMotor	= new CwrTailMotor  (PORT_A);	// �e�[�����[�^�[
	m_pCClock		= new CwrClock();				// �N���b�N

	m_pCBattery		= new CwrBattery();			// �o�b�e���[
	m_pCLEDLight	= new CwrLEDLight();		// LED
	m_pCSpeaker		= new CwrSpeaker();			// �X�s�[�J�[
}

CDeviceInterface::~CDeviceInterface()	// �f�X�g���N�^�[
{
	delete	m_pCTouchSensor;	// �^�b�`�Z���T�[
	delete	m_pCSonarSensor;	// �\�i�[�Z���T�[
	delete	m_pCColorSensor;	// �J���[�Z���T�[
	delete	m_pCGyroSensor;		// �W���C���Z���T�[
	delete	m_pCLeftMotor;		// �ԗփ��[�^�[ L
	delete	m_pCRightMotor;		// �ԗփ��[�^�[ R
	delete	m_pCTailMotor;		// �e�[�����[�^�[
	delete	m_pCClock;			// �N���b�N

	delete	m_pCBattery;		// �o�b�e���[
	delete	m_pCLEDLight;		// LED
	delete	m_pCSpeaker;		// �X�s�[�J�[
}


///////////////////////////////////////////////////
//	CwrTouchSensor		�^�b�`�Z���T�[
///////////////////////////////////////////////////
CwrTouchSensor::CwrTouchSensor( ePortS port ) : // �R���X�g���N�^�[
	TouchSensor( port )
{
}
CwrTouchSensor::~CwrTouchSensor()	// �f�X�g���N�^�[
{
}

///////////////////////////////////////////////////
//	CwrSonarSensor		�\�i�[�Z���T�[
///////////////////////////////////////////////////
CwrSonarSensor::CwrSonarSensor( ePortS port ) :	// �R���X�g���N�^�[
	SonarSensor( port )
{
}
CwrSonarSensor::~CwrSonarSensor()	// �f�X�g���N�^�[
{
}

///////////////////////////////////////////////////
//	CwrColorSensor		�J���[�Z���T�[
///////////////////////////////////////////////////
CwrColorSensor::CwrColorSensor( ePortS port ) :	// �R���X�g���N�^�[
	ColorSensor( port )
{
}
CwrColorSensor::~CwrColorSensor()	// �f�X�g���N�^�[
{
}

///////////////////////////////////////////////////
//	CwrGyroSensor		�W���C���Z���T�[
///////////////////////////////////////////////////
CwrGyroSensor::CwrGyroSensor( ePortS port ) :	// �R���X�g���N�^�[
	GyroSensor( port )
{
}
CwrGyroSensor::~CwrGyroSensor()	// �f�X�g���N�^�[
{
}

///////////////////////////////////////////////////
//	CwrMotor		���[�^�[
///////////////////////////////////////////////////
CwrMotor::CwrMotor( ePortM port ) :	// �R���X�g���N�^�[
	Motor( port )
{
}
CwrMotor::~CwrMotor()	// �f�X�g���N�^�[
{
}

///////////////////////////////////////////////////
//	CwrWheelMotor		�ԗփ��[�^�[
///////////////////////////////////////////////////
CwrWheelMotor::CwrWheelMotor( ePortM port ) : CwrMotor( port )	// �R���X�g���N�^�[
{
}
CwrWheelMotor::~CwrWheelMotor()	// �f�X�g���N�^�[
{
}

///////////////////////////////////////////////////
//	CwrTailMotor		�e�[�����[�^�[
///////////////////////////////////////////////////
CwrTailMotor::CwrTailMotor( ePortM port ) : CwrMotor( port )	// �R���X�g���N�^�[
{
}
CwrTailMotor::~CwrTailMotor()	// �f�X�g���N�^�[
{
}

///////////////////////////////////////////////////
//	CwrClock		�N���b�N
///////////////////////////////////////////////////
CwrClock::CwrClock() : Clock()	// �R���X�g���N�^�[
{
}
CwrClock::~CwrClock()	// �f�X�g���N�^�[
{
}

///////////////////////////////////////////////////
//	CwrBattery		�o�b�e���[
///////////////////////////////////////////////////
CwrBattery::CwrBattery()	// �R���X�g���N�^�[
{
}
CwrBattery::~CwrBattery()	// �f�X�g���N�^�[
{
}
int	CwrBattery::GetmA()	// �o�b�e���̓d�����擾����D�imA�j
{
	return	ev3_battery_current_mA();
}
int	CwrBattery::GetmV()	// �o�b�e���̓d�����擾����D�imV�j
{
	return	ev3_battery_voltage_mV();
}

///////////////////////////////////////////
//	CwrLEDLight	LED
///////////////////////////////////////////
CwrLEDLight::CwrLEDLight()	// �R���X�g���N�^�[
{
}
CwrLEDLight::~CwrLEDLight()	// �f�X�g���N�^�[
{
}
ER	CwrLEDLight::SetColor( ledcolor_t	color )	// LED���C�g�̃J���[��ݒ肷��
{
	return	ev3_led_set_color (color);
}

///////////////////////////////////////////
//	CwrSpeaker	�X�s�[�J�[
///////////////////////////////////////////
CwrSpeaker::CwrSpeaker()	// �R���X�g���N�^�[
{
}
CwrSpeaker::~CwrSpeaker()	// �f�X�g���N�^�[
{
}

ER 	CwrSpeaker::SetVolume(uint8_t nVolume)	// ���ʂ𒲐�����D
{
	return	ev3_speaker_set_volume(nVolume);
}
ER 	CwrSpeaker::PlayTone(					// �w�肵�����g���Ńg�[���o�͂���D���Đ����Ă���T�E���h�͒�~�����
					uint16_t nFrequency,	// �g�[���̎��g��
					int32_t nDuration		// �o�͎������ԁD�P�ʁF�~���b�DSOUND_MANUAL_STOP���w�肵���ꍇ�͎蓮�Œ�~����D
					)
{
	return	ev3_speaker_play_tone( nFrequency,nDuration );
}
ER 	CwrSpeaker::PlayFile(					// �w�肵��WAV�t�@�C���i8-bit 8kHz mono�j���Đ�����D
					const memfile_t *p_memfile,	// WAV�t�@�C���̃������t�@�C���ւ̃|�C���^
					int32_t nDuration			// �o�͎������ԁD�P�ʁF�~���b�DSOUND_MANUAL_STOP���w�肵���ꍇ�͎蓮�Œ�~���Ȃ��ƍŌ�܂ōĐ�����D
					)
{
	return	ev3_speaker_play_file( p_memfile, nDuration );
}
ER 	CwrSpeaker::Stop()						// ���Đ����Ă���T�E���h���~����D [�ډ�]
{
	return	ev3_speaker_stop();
}

