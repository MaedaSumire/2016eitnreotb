#ifndef STARTCONTROLLER_H_
#define STARTCONTROLLER_H_

#include "ev3api.h"
#include "StartInstructionGet.h"
#include "PostureAdjustment.h"
#include "Clock.h"

class StartController {
public:

	StartController(StartInstructionGet* startinstructionget,PostureAdjustment* postureadjustment,
					ev3api::Clock& clock);
	void StartDicision();

private:
	StartInstructionGet* mStartInstructionGet;
	PostureAdjustment* mPostureAdjustment;
	ev3api::Clock& mClock;
};

#endif  // STARTCONTROLLER_H_
