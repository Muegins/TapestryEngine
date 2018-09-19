#ifndef CONTEXT_H
#define CONTEXT_H

#include "Utils.h"
#include "Console.h"
#include "Event.h"
#include "Mapper.h"
#include "MiscDraw.h"

class Context
{
public:

	Context() {}

	virtual bool Load(const char* filename) = 0;

	virtual bool Update() = 0;

	SDL_Renderer* mRen;
	EventFeed mFeed;

protected:
};

class ContextManager : public EventReceiver
{
public:

	ContextManager() {}

	ContextManager(char* GameDataPath) : mGameDataPath(GameDataPath) {}

	bool LogContext(Context* con, char* name);

	bool LoadContext(char* ContextName);

	bool ContextUpdate();

	bool EventProcess(Event eve);

protected:
	
	char* mGameDataPath;
	Context* mActiveContext;
	std::vector<Context*> mContexts;
	std::vector<char*>    mNames;

};


class GameOver : public Context, public EventReceiver
{
public:

	GameOver() {};

	GameOver(SDL_Renderer* ren, SDL_Texture* splash)
	{
		mRen = ren;
		mSplash = splash;
	}

	bool Update();

	bool EventProcess(Event eve);

	EventFeed mFeed;

protected:

	SDL_Texture* mSplash;

};

class MapTest : public Context
{
public:

	MapTest(SDL_Renderer* ren) : mRen(ren)
	{
		mMapper = new Mapper();
	}

	bool Load(const char* filename)
	{
		cJSON* root = LoadJSON(filename);
		//PrintJSON(root);
		cJSON* map_test = cJSON_GetObjectItem(root, "map_test");
		int h = cJSON_GetObjectItem(map_test, "h")->valueint;
		int w = cJSON_GetObjectItem(map_test, "w")->valueint;

		mMapper->GenerateMap(h, w);
		return false;
	}

	bool Update()
	{
		mMapper->AddFeature();
		DrawMapTest(mRen, mMapper->GetMap());
		return false;
	}

protected:

	SDL_Renderer* mRen;
	Mapper* mMapper;
};

#endif
