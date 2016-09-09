/////////////////////////////////////////////////
// バランサー　ラッパークラス

#ifndef WR_BALANCER_H_INCLUDED_
#define WR_BALANCER_H_INCLUDED_

#include "ev3api.h"
//#include	"balancer.h"

class CWrBalancer
{
public:
	CWrBalancer();		// コンストラクター
	~CWrBalancer();		// デストタクター

protected:
	int	m_nPwmL;	// モータPWM値　Ｌ
	int	m_nPwmR;	// モータPWM値　Ｒ

public:
	void	Init();		// 倒立振子API初期化

	void BalanceControl(	// バランサーコントロール
		float args_cmd_forward,
		float args_cmd_turn,
		float args_gyro,
		float args_gyro_offset,
		float args_theta_m_l,
		float args_theta_m_r,
		float args_battery
	);

	int	GetPwmL();	// モータPWM値取得　Ｌ
	int	GetPwmR();	// モータPWM値取得　Ｒ
};
#endif // WR_BALANCER_H_INCLUDED_
