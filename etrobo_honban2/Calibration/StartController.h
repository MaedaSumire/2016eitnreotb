#ifndef STARTCONTROLLER_H_
#define STARTCONTROLLER_H_

#include "ev3api.h"
#include "StartInstructionGet.h"

class StartController {
public:

	StartController(StartInstructionGet* startinstructionget);
	void StartDicision();

private:
	StartInstructionGet* mStartInstructionGet;
};

#endif  // STARTCONTROLLER_H_
