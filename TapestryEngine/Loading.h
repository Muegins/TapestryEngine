#ifndef LOADING_H
#define LOADING_H

#include "Utils.h"
#include "Console.h"
#include "Context.h"
#include "Event.h"

class Loading : public Context
{
public:
	
	Loading() {};

	Loading(SDL_Renderer* ren)
	{
		mRen = ren;
	}

	bool Load(const char* filename);

	bool Update();

	EventFeed mFeed;

protected:

	SDL_Texture* mSplash;

};

#endif
