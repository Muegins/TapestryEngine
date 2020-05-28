#ifndef ACTORHANDLE_H
#define ACTORHANDLE_H

#include "Console.h"
#include "Event.h"
#include "Utils.h"
#include "Actor.h"

struct HandleBind
{
	ActHandle mID;
	EventReceiver* mAct;
};

class ActorHandleManager : public EventReceiver
{
public:

	ActorHandleManager() : mNextNewID(0)
	{
		mHandleTree = BinaryTree();
		//mHandleTree = &Node(mNextID);
	}

	int AssignHandle(Actor* act)
	{
		//HandleBind hb = { mNextID, act };
		//mHandles.push_back(hb); //record the handle and Actor/EventReceiverPointer

		//Node* Bind = new Node(mNextID, act);

		mHandleTree.Insert(mNextNewID, act);

		mNextNewID++;

		return mNextNewID-1;
		//return hb.mHandle;
	}

	int ReclaimHandle(int id) //I'm not sure if recycling ID's makes sense or how to do it
	{
		//mHandleTree.Search(id)->Delete()
		return 0;
	}

	Actor* GetActorAddress(int id)
	{
		Actor* Address = (Actor*)(mHandleTree.Search(id))->GetData();
		if (Address == NULL)
		{
			return NULL;
		}
		else
		{
			return Address;
		}
	}

	bool EventProcess(Event eve)
	{
//		switch (*eve.GetEventType())
//		{
//		case ASSIGN_HANDLE:
//			
//			gCons->ConsPrintf("Handle Assigned to actor\n");
//			return AssignHandle((Actor*)eve.GetReturnAddress());
//			break;
//		case GET_ACTOR_ADDRESS:
//			return GetActorAddress(eve.GetEventData()->i);
//			break;
//		default:
//			gCons->ConsPrintf("Actor Handle Manager received unrecognized event\n");
//			return false;
//			break;
//		}
		return true;
	}

protected:

	int UpdateNextHandle() // see reclaim handle
	{
		return 0;
	}

	int mNextNewID;
	BinaryTree mHandleTree;

};

#endif 
