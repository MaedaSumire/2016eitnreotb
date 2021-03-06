//区間判断コントローラ
#include "SectionDecisionController.h"

SectionDecisionController::SectionDecisionController(
		DeviceInterface* pDeviceInterface
		)
{
	m_pDeviceValueGet	= new DeviceValueGet(pDeviceInterface);
}

SectionDecisionController::~SectionDecisionController()
{
	delete	m_pDeviceValueGet;
}

//DV = DeviceValue
//メソッド：int 現区間を特定する（現区間の番号）　return 現区間の番号
int SectionDecisionController::SectionIdentify(int now_section){

	DV dv;
	bool result;

	//デバイス値を取ってくる
	dv = m_pDeviceValueGet->DeviceValueGetter();

	//区間切替判断させる
	result = m_SectionDecision.SwitchingDecision(dv,now_section);

	//切替判断であれば　現区間＋１　する
	if(result){
		now_section += 1;
	}

	return now_section;
}
