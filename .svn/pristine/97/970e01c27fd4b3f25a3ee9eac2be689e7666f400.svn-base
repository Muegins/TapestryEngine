#include "Animation.h"

//FramesetFunctions
FrameSet::FrameSet(SDL_Renderer* ren, const char* SourcePath, int FrameCount, int FRate, int frameH, int frameW)
{
	memset(mFrames, 0, 256);
//	gCons->ConsPrintf("image source path: %s\n", SourcePath);
	mframesource = SDL_CreateTextureFromSurface(ren, LoadSurfaceBMP(SourcePath));
	mFrameCount = (FrameCount - 1);
	mDefaultFrameRate = FRate;

	SDL_Rect framerect;
	framerect.h = frameH;
	framerect.w = frameW;
	framerect.x = 0;
	framerect.y = 0;

	int i = 0;
	while (i <= mFrameCount)
	{

		framerect.x = ((i)*frameW);

		mFrames[i] = framerect;

		i++;
	}
}

//animation Functions
animation::animation(FrameSet* set, int ID, bool flip) : mID(ID)
{
	mFrameSet = set;
	mCurrentFrameNumber = 0;
	mFrameRate = mFrameSet->GetDefaultFrameRate();
	mTimer = 0;
	mIsFlippable = flip;
	mIsPlaying = false;
	mCurrentFrame.FrameSource = mFrameSet->GetFrameSource();
	mCurrentFrame.FrameRect = mFrameSet->GetFrameRect(mCurrentFrameNumber);
}

Frame animation::GetCurrentFrame()
{
	mCurrentFrame.FrameRect = mFrameSet->GetFrameRect(mCurrentFrameNumber);
	if (mIsPlaying == true)
	{
		if ((gTime->GetCurrentMS() - mTimer) >= mFrameRate)
		{
			if (mCurrentFrameNumber == mFrameSet->GetNumberOfFrames())
			{
				if (mFlags == ONCE)
				{
					Stop();
					mFeed.EventProcess(Event(ANIM_COMPLETE, mID));
					//gCons->ConsPrintf("Animation Complete\n");
				}

				mCurrentFrameNumber = 0;
			}
			else
			{
				mCurrentFrameNumber = (mCurrentFrameNumber + 1);
			}
			mTimer = gTime->GetCurrentMS();
		}
	}
	return mCurrentFrame;
}

//AnimDataPack Functions
AnimDataPack::AnimDataPack(int AnimCount, FrameSet* AnimData, int* Index)
{
	mAnimData = AnimData;
	mIndexer = Index;
	mAnimCount = AnimCount;
}

FrameSet* AnimDataPack::GetAnimationData(int AnimationID)
{
	for (int i = 0; i < mAnimCount; i++)
	{
		//if (AnimationID == 130) { gCons->ConsPrintf("index: %i, item: %i\n", i, mIndexer[i]); }
		if (mIndexer[i] == AnimationID)
		{
			return &mAnimData[i];
		}
	}
	gCons->ConsPrintf("Invalid Animation ID; Could not find Animation Data\n");
	return NULL;
}

//AnimPack Functions
AnimPack::AnimPack(AnimDataPack* data)
{
	mData = data;
	mLastIndex = 0;

	mAnims = new animation[mData->GetAnimCount()];
	for (int i = 0; i < mData->GetAnimCount(); i++)
	{
		mAnims[i] = animation( mData->GetAnimationData(mData->GetIndex(i)), mData->GetIndex(i) ); //make sure mData->GetIndex(i) returns correct ID
	}
}

animation* AnimPack::ActivateAnimation(int AnimationID, int flags)
{
	for (int i = 0; i < mData->GetAnimCount(); i++)
	{
		if (mData->GetIndex(i) == AnimationID)
		{
			if (mLastIndex != i)
			{
				mAnims[mLastIndex].Stop();
				mLastIndex = i;
			}

			mAnims[i].Play(flags);
			return &mAnims[i];
		}
	}
	gCons->ConsPrintf("Invalid Animation ID; Could not find Animation\n");
	return NULL;

}

bool FrameCompare(Frame f1, Frame f2)
{
	if (f1.FrameSource == f2.FrameSource)
	{
		if (f1.FrameRect.x == f2.FrameRect.x)
		{
			return true;
		}
	}
	return false;
}