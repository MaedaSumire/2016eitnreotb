//区間走行データ取得
#include "RunningDataGet.h"


RunningDataGet::RunningDataGet()
{
}

//RD = RunningData
//メソッド： RD 現区間走行データを取得する（現区間の番号）　return 現区間走行データ
RD RunningDataGet::RunningDataGetter(int now_section){

	RD rd;

	rd = mRunningData.referData(now_section);

	return rd;
}
