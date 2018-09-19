#include "AnimationGraph.h"

//AnimGraphData functions
bool AnimGraphData::DefineLoop(int AnimID)
{
	if (mAnimData.GetAnimationData(AnimID) != NULL)
	{
		mLoopsAnimIDs.push_back(AnimID);
		return true;
	}
	else
	{
		gCons->ConsPrintf("Invalid animation ID, Animation Graph could not define loop\n");
		return false;
	}
}

bool AnimGraphData::DefineTransitions(int AnimID)
{
	if (mAnimData.GetAnimationData(AnimID) != NULL)
	{
		mTransitionsAnimIDs.push_back(AnimID);
		return true;
	}
	return false;
}

bool AnimGraphData::DefineFireables(int AnimID)
{
	if (mAnimData.GetAnimationData(AnimID) != NULL)
	{
		mFireablesAnimIDs.push_back(AnimID);
		return true;
	}
	else
	{
		gCons->ConsPrintf("Invalid animation ID, Animation Graph could not define fireable\n");
		return false;
	}
}

bool AnimGraphData::CreateTranisitionMatrix() //call only after all loops have been defined
{
	mTransitionMatrix = new int*[mLoopsAnimIDs.size()];

	for (int i = 0; i < (int)mLoopsAnimIDs.size(); i++)
	{
		mTransitionMatrix[i] = new int[mLoopsAnimIDs.size()];
		for (int j = 0; j < (int)mLoopsAnimIDs.size(); j++)
		{
			mTransitionMatrix[i][j] = -1; //-1 represents no transition
		}
	}
	return true;
}

bool AnimGraphData::PopulateTransitionMatrix(int initState, int targetState, int transitionID)
{
	int initIndex = -1;
	int targetIndex = -1;

	for (int i = 0; i < (int)mLoopsAnimIDs.size(); i++)
	{
		if (initState == mLoopsAnimIDs.at(i))
		{
			initIndex = i;
		}
		if (targetState == mLoopsAnimIDs.at(i))
		{
			targetIndex = i;
		}
	}

	if ((initIndex != -1) && (targetIndex != -1))
	{
		mTransitionMatrix[initIndex][targetIndex] = transitionID;
		return true;
	}
	return false;
}

//Anim Graph Functions
int AnimGraph::GetTransitionID(int initState, int targetState)
{
	int initIndex = -1;
	int targetIndex = -1;

	for (int i = 0; i < (int)mAGD->mLoopsAnimIDs.size(); i++)
	{
		if (initState == mAGD->mLoopsAnimIDs.at(i))
		{
			initIndex = i;
		}
		if (targetState == mAGD->mLoopsAnimIDs.at(i))
		{
			targetIndex = i;
		}
	}

	if ((initIndex != -1) && (targetIndex != -1))
	{
		return mAGD->mTransitionMatrix[initIndex][targetIndex];
	}
	else
	{
		return -1;
	}
}

Frame* AnimGraph::UpdateAnimation()
{
	if (mState != *mActorState)
	{
		if ( (GetTransitionID(mState, *mActorState) != -1) && mState != 0 )
		{
			mCurrentFrame = mAnimPack.ActivateAnimation(GetTransitionID(mState, *mActorState), ONCE)->GetCurrentFrame();
			return &mCurrentFrame;
		}
		else
		{
			mState = *mActorState;
			return &mCurrentFrame;
		}
	}
	else
	{
		for (int i = 0; i < (int)mAGD->mLoopsAnimIDs.size(); i++)
		{
			if (mAGD->mLoopsAnimIDs.at(i) == mState)
			{
				mCurrentFrame = mAnimPack.ActivateAnimation(mAGD->mLoopsAnimIDs.at(i))->GetCurrentFrame();
				return &mCurrentFrame;
			}
		}
	}
	return NULL;
}

Frame* AnimGraph::PlayOnce(int AnimID)
{
	mCurrentFrame = mAnimPack.ActivateAnimation(AnimID, ONCE)->GetCurrentFrame();
	return &mCurrentFrame;
}

bool AnimGraph::EventProcess(Event eve)
{
	switch (*eve.GetEventType())
	{
	case ANIM_COMPLETE:
		mState = *mActorState;
		mFeed.EventProcess(Event(ANIM_COMPLETE, eve.GetEventData()->i));
		return true;
	default:
		gCons->ConsPrintf("Animation Graph asked to process unrecgonized event\n");
		return false;
	}
}