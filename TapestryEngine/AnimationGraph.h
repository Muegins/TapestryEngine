#ifndef ANIMATION_GRAPH_H
#define ANIMATION_GRAPH_H

#include "Utils.h"
#include "Console.h"
#include "Animation.h"
#include "Event.h"

class AnimGraphData
{
public:

	AnimGraphData() {}

	//AnimGraph(int* state) : mActorState(state) {}

	AnimGraphData(AnimDataPack animdata) : mAnimData(animdata) {}

	bool DefineLoop(int AnimID);
	
	bool DefineTransitions(int AnimID);

	bool DefineFireables(int AnimID);

	bool CreateTranisitionMatrix(); //call only after all loops have been defined

	bool PopulateTransitionMatrix(int initState, int targetState, int transitionID);

	int GetLoopIDIndex(int index)
	{
		return mLoopsAnimIDs.at(index);
	}

	AnimDataPack* GetAnimData()
	{
		return &mAnimData;
	}

	int GetH()
	{
		return mAnimData.GetFrameH();
	}

	int GetW()
	{
		return mAnimData.GetFrameW();
	}

	std::vector<int> mLoopsAnimIDs;
	std::vector<int> mTransitionsAnimIDs;
	std::vector<int> mFireablesAnimIDs;
	int** mTransitionMatrix;

protected:

	AnimDataPack mAnimData;
	
};
 

class AnimGraph : public EventReceiver
{
public:

	AnimGraph() {};

	AnimGraph(AnimGraphData* AGD) 
	{
		mAGD = AGD;
		mAnimPack = AnimPack(mAGD->GetAnimData());

		for (int i = 0; i < (int)mAGD->mTransitionsAnimIDs.size(); i++)
		{
			mAnimPack.GetAnimation(mAGD->mTransitionsAnimIDs.at(i))->mFeed.Subscribe(this);
		}
	}

	void GiveActorState(int* state)
	{
		mActorState = state;
		mState = *mActorState;
	}

	int GetTransitionID(int initState, int targetState);

	Frame* UpdateAnimation();

	Frame* PlayOnce(int AnimID);

	bool EventProcess(Event eve);
	
	AnimPack* GetAnimPack()
	{
		return &mAnimPack;
	}

	int GetH()
	{
		return mAGD->GetH();
	}

	int GetW()
	{
		return mAGD->GetW();
	}

	EventFeed mFeed;

protected:

	AnimGraphData* mAGD;
	AnimPack mAnimPack;

	int* mActorState;
	int mState;

	Frame mCurrentFrame;
};
#endif