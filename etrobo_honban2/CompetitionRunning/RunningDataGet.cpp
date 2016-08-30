#include "RunningDataGet.h"

RunningDataGet::RunningDataGet(RunningData* RunningData)
	:mRunningData(RunningData){
}

RD RunningDataGet::RunningDataGetter(int now_section){

	RD rd;

	rd = mRunningData -> referData(now_section);

	return rd;
}
