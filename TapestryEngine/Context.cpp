#include "Context.h"

bool ContextManager::LogContext(Context* con, const char* name)
{
	mContexts.push_back(con);
	mNames.push_back(name);
	return false;
}

bool ContextManager::LoadContext(const char* ContextName)
{
	for (int i = 0; i < (int)mNames.size(); i++)
	{
		if (!strcmp(ContextName, mNames.at(i)))
		{
			mContexts.at(i)->Load(mGameDataPath);
			mActiveContext = mContexts.at(i);
			return true;
		}
	}
	gCons->ConsPrintf("Unable to load context; No context matching name %s was found\n", ContextName);
	return false;
}

bool ContextManager::ContextUpdate()
{
	return mActiveContext->Update();
}

bool ContextManager::EventProcess(Event eve)
{
	return false;
}

bool GameOver::Update()
{
	SDL_RenderCopy(mRen, mSplash, NULL, NULL);

	return true;
}

bool GameOver::EventProcess(Event eve)
{
	switch (*eve.GetEventType())
	{
	case KEY_DOWN:
		switch (eve.GetEventData()->i)
		{
		case SDL_SCANCODE_R:
			//reload level;
			break;
		}
		break;
	default:

		return false;
	}

	return false;
}

