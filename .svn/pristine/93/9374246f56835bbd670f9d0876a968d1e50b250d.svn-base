#ifndef INPUT_H
#define INPUT_H

#include "Utils.h"
#include "Event.h"

struct KeyboardState
{
	bool mQ;
	bool mW;
	bool mE;
	bool mLEFT;
	bool mRIGHT;
	bool mUP;
	bool mDOWN;
};

class Control
{
public:

	Control();

	bool SendKeyEvent(int KeyID, int KeyState);

	void ProcessKeyboard();

	EventFeed mFeed;

protected:

	//KeyboardState mkeys;

	const Uint8* mKeyState;
	Uint8 mLastState[512];
};

#endif