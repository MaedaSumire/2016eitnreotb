#include "SectionRunningData.h"

SectionRunningData::SectionRunningData()
{

}

SRD SectionRunningData::referData(int now_section){

	SRD srd;

	double mKP[7] = {1.4,1.4,1.4,1.4,1.4,1.4,1.4};
	double mKI[7] = {0.2,0.2,0.2,0.2,0.2,0.2,0.2};
	double mKD[7] = {0.02,0.02,0.02,0.02,0.02,0.02,0.02};
	double mforward[7] = {30,30,30,30,30,30,30};

	srd.KP = mKP[now_section];
	srd.KI = mKI[now_section];
	srd.KD = mKD[now_section];
	srd.forward = mforward[now_section];

	return srd;
}
