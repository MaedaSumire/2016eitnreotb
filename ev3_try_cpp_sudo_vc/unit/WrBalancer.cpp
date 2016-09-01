/////////////////////////////////////////////////
// バランサー　ラッパークラス

#include	"../balancer.h"
#include	"WrBalancer.h"


CWrBalancer::CWrBalancer()		// コンストラクター
{
	m_nPwmL	= 0;	// モータPWM値　Ｌ
	m_nPwmR	= 0;	// モータPWM値　Ｒ
}

CWrBalancer::~CWrBalancer()		// デストタクター
{
}

void	CWrBalancer::Init()		// 倒立振子API初期化
{
	balance_init();
}

void CWrBalancer::BalanceControl(	// バランサーコントロール
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

	balance_control(	// バランサーコントロール
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

	m_nPwmL	= cRetPwmL;	// モータPWM値　Ｌ
	m_nPwmR	= cRetPwmR;	// モータPWM値　Ｒ
}

int	CWrBalancer::GetPwmL()	// モータPWM値取得　Ｌ
{
	return	m_nPwmL;
}

int	CWrBalancer::GetPwmR()	// モータPWM値取得　Ｒ
{
	return	m_nPwmR;
}
