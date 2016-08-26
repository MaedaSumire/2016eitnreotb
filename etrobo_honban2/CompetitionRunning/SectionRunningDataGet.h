#ifndef SECTIONRUNNINGDATAGET_H_
#define SECTIONRUNNINGDATAGET_H_

#include "ev3api.h"
#include "SectionRunningData.h"

class SectionRunningDataGet {
public:

	SectionRunningDataGet(SectionRunningData* SectionRunningData);
	SRD SectionRunningDataGetter(int now_section);


private:

	SectionRunningData mSectionRunningData;

};

#endif  // SECTIONRUNNINGDATAGET_H_
