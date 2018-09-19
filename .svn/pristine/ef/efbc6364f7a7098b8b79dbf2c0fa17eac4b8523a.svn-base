#include "Event.h"

bool EventFeed::Subscribe(EventReceiver* sub)
{
	for (int i = 0; i < (int)mSubs.size(); i++)
	{
		if (mSubs.at(i) == NULL)
		{
			mSubs.at(i) = sub;
			return true;
		}
	}
	mSubs.push_back(sub);
	return false;
}

bool EventFeed::Unsubscribe(EventReceiver* sub)
{
	for (int i = 0; i < (int)mSubs.size(); i++)
	{
		if (mSubs.at(i) == sub)
		{
			mSubs.at(i) = NULL;
			return true;
		}
	}
	return false;
}

bool EventFeed::EventProcess(Event eve)
{
	if (*eve.GetEventType() == UNSUBSCRIBE)
	{
		return Unsubscribe((EventReceiver*)eve.GetEventData());
	}
	
	for (int i = 0; i < (int)mSubs.size(); i++)
	{
		mSubs.at(i)->EventProcess(eve);
	}
	return true;
}