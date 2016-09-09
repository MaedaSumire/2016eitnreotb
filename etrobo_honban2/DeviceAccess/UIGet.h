#ifndef EV3_APP_UIGET_H_
#define EV3_APP_UIGET_H_

#include "DeviceInterface.h"

typedef struct{
	char Button;	// EV3 �{�̃{�^��
	uint8_t btcKey;	// �u���[�c�[�X�ʐM�@��@�L�[�{�[�h����
	bool touch;		// EV3�^�b�`�Z���T�[
} UI ;

typedef struct{		// �u���[�c�[�X�\����
	uint8_t btcKey;	// �u���[�c�[�X�ʐM�@��@�L�[�{�[�h����
	FILE* pBtFile;	// �u���[�c�[�XFILE�|�C���^�[
	char* pcLogBuff;	// ���O�o�͗p������o�b�t�@�[�|�C���^�[(�g�p���Ƀ������[�m�ۂ���Ǝ��Ԃ��|����ׁA�����Ɋm�ۂ���)
} BLUET ;

class UIGet {
public:
	UIGet(DeviceInterface* pDeviceInterface);	// �R���X�g���N�^�[

	UI UIGetter();

	BLUET*	GetBlueT();	// �u���[�c�[�X�C���X�^���X�擾

	void	WriteLog(char* cBuff);	// �u���[�c�[�X���O�o��

private:
	DeviceInterface* m_pDeviceInterface;

	char	mLogBuff[256];	// ���O�o�͗p������o�b�t�@�[
	BLUET	mBlueT;		// �u���[�c�[�X�C���X�^���X
};

#endif  // EV3_APP_UIGET_H_
