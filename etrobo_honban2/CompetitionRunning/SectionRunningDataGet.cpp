#include "SectionRunningDataGet.h"

SectionRunningDataGet::SectionRunningDataGet(SectionRunningData* SectionRunningData)
	:mSectionRunningData(){
}

SRD SectionRunningDataGet::SectionRunningDataGetter(int now_section){

	SRD srd;

	srd = mSectionRunningData.referData(now_section);

	return srd;
}
