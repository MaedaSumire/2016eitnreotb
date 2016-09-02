#ifndef STARTINSTRUCTIONGET_H_
#define STARTINSTRUCTIONGET_H_

#include "ev3api.h"
#include "UIGet.h"

class StartInstructionGet {
public:

	StartInstructionGet(UIGet* uiget);
	bool StartInstructionGetter();

private:
	UIGet* mUIGet;
};

#endif  // STARTINSTRUCTIONGET_H_
