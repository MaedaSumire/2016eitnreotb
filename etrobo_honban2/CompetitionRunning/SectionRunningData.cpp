#include "SectionRunningData.h"

SectionRunningData::SectionRunningData()
{
	mKP[7] = {1,2,3,4,5,6,7};
	mKI[7] = {1,2,3,4,5,6,7};
	mKD[7] = {1,2,3,4,5,6,7};
	mforward[7] = {1,2,3,4,5,6,7};

	typedef struct{
		double KP;
		double KI;
		double KD;
		double forward;
	} SRD ;

}

SRD SectionRunningData::referData(int now_section){

	SRD srd;

	srd.KP = mKP[now_section];
	srd.KI = mKI[now_section];
	srd.KD = mKD[now_section];
	srd.forward = mforward[now_section];

	return srd;
}
