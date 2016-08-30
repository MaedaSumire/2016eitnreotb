#ifndef RUNNINGDATAGET_H_
#define RUNNINGDATAGET_H_

#include "ev3api.h"
#include "RunningData.h"

class RunningDataGet {
public:

	RunningDataGet(RunningData* runningdata);
	RD RunningDataGetter(int now_section);


private:

	RunningData* mRunningData;

};

#endif  // SECTIONRUNNINGDATAGET_H_
