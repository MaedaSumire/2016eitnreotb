2016.09.05 M.SUDO

�P�D�L�����u���[�V�����擾�@�\��ǉ�
�@CalibrationController�N���X�Ɏ������܂����B
  
�@�L�����u���[�V�����̒l�͎��̍\���̂ƂȂ�܂��B�@
  typedef struct{		// �␳�l�\����
	int8_t	White;	// �P�x�@��
	int8_t	Black;	// �P�x�@��
	int8_t	Half;	// �P�x�@���Ԓl
	float	TailAngleStandUp;	// �������K���p�x
  } CALIBRAT ;

�@�L�����u���[�V�������Ɏ��̃L�[�������ŋP�x���擾���܂��B
�@�@w : ��
�@�@b : ��
�@�@h : ���Ԓl

�Q�D�u���[�c�[�X�n�@�\��ǉ�
�@UIGet�N���X�Ɏ������܂����B
�@���O�o�͂�RunningController::RunningExecute()���Q�l�ɂ��ĉ������B

�R�D���̑�
�@�E���̃N���X�̎g�p����߂܂����B�i�\�[�X�R�[�h�͎c���Ă܂��j
�@�@ColorGet
�@�@PostureAdjustment
�@�@StartInstructionGet
�@�@���R�F�Z���T�[����{�^����L�[�{�[�h�擾�𓯂����[�v����
�@�@�@�@�@�F�X�ȏꏊ�ōs���Ɗ����l���擾�ł��Ȃ��Ȃ邽�߁B
�@�@�@�@
�@�E�e�N���X�̃R���X�g���N�^�[������ύX�������̂�����܂��B
�@�@�傫�������������Ƃ��v�����̂ł����A���Ԃ��Ȃ��̂ŏ��������ɗ��߂܂����B

