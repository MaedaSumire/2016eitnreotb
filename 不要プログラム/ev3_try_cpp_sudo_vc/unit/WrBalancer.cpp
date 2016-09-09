/////////////////////////////////////////////////
// �o�����T�[�@���b�p�[�N���X

#include	"../balancer.h"
#include	"WrBalancer.h"


CWrBalancer::CWrBalancer()		// �R���X�g���N�^�[
{
	m_nPwmL	= 0;	// ���[�^PWM�l�@�k
	m_nPwmR	= 0;	// ���[�^PWM�l�@�q
}

CWrBalancer::~CWrBalancer()		// �f�X�g�^�N�^�[
{
}

void	CWrBalancer::Init()		// �|���U�qAPI������
{
	balance_init();
}

void CWrBalancer::BalanceControl(	// �o�����T�[�R���g���[��
		float args_cmd_forward,
		float args_cmd_turn,
		float args_gyro,
		float args_gyro_offset,
		float args_theta_m_l,
		float args_theta_m_r,
		float args_battery
	)
{

	signed char cRetPwmL;
	signed char cRetPwmR;

	balance_control(	// �o�����T�[�R���g���[��
		args_cmd_forward,
		args_cmd_turn,
		args_gyro,
		args_gyro_offset,
		args_theta_m_l,
		args_theta_m_r,
		args_battery,
		&cRetPwmL,
		&cRetPwmR
	);

	m_nPwmL	= cRetPwmL;	// ���[�^PWM�l�@�k
	m_nPwmR	= cRetPwmR;	// ���[�^PWM�l�@�q
}

int	CWrBalancer::GetPwmL()	// ���[�^PWM�l�擾�@�k
{
	return	m_nPwmL;
}

int	CWrBalancer::GetPwmR()	// ���[�^PWM�l�擾�@�q
{
	return	m_nPwmR;
}
