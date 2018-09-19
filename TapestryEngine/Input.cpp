#include "Input.h"

Control::Control()
{
	mKeyState = SDL_GetKeyboardState(NULL);
	memcpy(mLastState, mKeyState, 512);
}

bool Control::SendKeyEvent(int KeyID, int KeyState)
{
	EventType et;
	if (KeyState == 1)
	{
		et = KEY_DOWN;
	}
	else // KeyState == 0
	{
		et = KEY_UP;
	}
	mFeed.EventProcess(Event(et, KeyID));

	return true;
}

void Control::ProcessKeyboard()
{
	SDL_PumpEvents(); //Update *mKeys

	for (int i = 0; i < 512; i++)
	{
		if (mLastState[i] != mKeyState[i])
		{
			SendKeyEvent(i, mKeyState[i]);
		}
	}

	memcpy(mLastState, mKeyState, 512);
}

