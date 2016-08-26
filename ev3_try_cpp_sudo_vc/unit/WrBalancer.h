/////////////////////////////////////////////////
// �o�����T�[�@���b�p�[�N���X

#ifndef WR_BALANCER_H_INCLUDED_
#define WR_BALANCER_H_INCLUDED_

#include "ev3api.h"
//#include	"balancer.h"

class CWrBalancer
{
public:
	CWrBalancer();		// �R���X�g���N�^�[
	~CWrBalancer();		// �f�X�g�^�N�^�[

protected:
	int	m_nPwmL;	// ���[�^PWM�l�@�k
	int	m_nPwmR;	// ���[�^PWM�l�@�q

public:
	void	Init();		// �|���U�qAPI������

	void BalanceControl(	// �o�����T�[�R���g���[��
		float args_cmd_forward,
		float args_cmd_turn,
		float args_gyro,
		float args_gyro_offset,
		float args_theta_m_l,
		float args_theta_m_r,
		float args_battery
	);

	int	GetPwmL();	// ���[�^PWM�l�擾�@�k
	int	GetPwmR();	// ���[�^PWM�l�擾�@�q
};
#endif // WR_BALANCER_H_INCLUDED_
