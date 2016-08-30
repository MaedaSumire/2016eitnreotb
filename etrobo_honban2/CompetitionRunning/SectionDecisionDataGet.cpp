#include "SectionDecisionDataGet.h"

SectionDecisionDataGet::SectionDecisionDataGet(SectionDecisionData* SectionDecisionData)
	:mSectionDecisionData(SectionDecisionData){
}

SDD SectionDecisionDataGet::SectionDecisionDataGetter(int now_section){

	SDD sdd;

	sdd = mSectionDecisionData -> referData(now_section);

	return sdd;
}
