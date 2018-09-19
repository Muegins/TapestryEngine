#ifndef ANIMATION_H
#define ANIMATION_H

#include "Utils.h"
#include "Event.h"

#define LOOP 0
#define ONCE 1

struct Frame
{
	SDL_Rect FrameRect;
	SDL_Texture* FrameSource;
};

class FrameSet
{
public:
	FrameSet() : mFrameCount(0), mFrames() {}

	FrameSet(SDL_Renderer* ren, const char* SourcePath, int FrameCount, int FRate, int frameH, int frameW);

	int GetNumberOfFrames()
	{
		return mFrameCount;
	}

	int GetDefaultFrameRate()
	{
		return mDefaultFrameRate;
	}

	SDL_Texture* GetFrameSource()
	{
		return mframesource;
	}

	SDL_Rect GetFrameRect(int framenumber)
	{
		//gCons->ConsPrintf("Frame Number = %i\n", framenumber);
		return mFrames[framenumber];
	}

	Frame GetFrame(int FrameNumber)
	{
		Frame frm;
		frm.FrameRect = GetFrameRect(FrameNumber);
		frm.FrameSource = mframesource;
		return frm;
	}

protected:
	int mFrameCount;
	int mDefaultFrameRate;
	SDL_Texture* mframesource;
	SDL_Rect mFrames[256];
};

class animation
{
public:

	animation() : mFrameSet(), mCurrentFrameNumber(0) {}

	animation(FrameSet* set, int ID, bool flip = true);

	Frame GetCurrentFrame();

	Frame GetFrame(int FrameNumber)
	{
		return mFrameSet->GetFrame(FrameNumber);
	}

	int GetCurrentFrameNumber()
	{
		return mCurrentFrameNumber;
	}

	bool SetPlaySpeed(int speed)
	{
		mFrameRate = speed;
	}

	bool IsFlippable()
	{
		return mIsFlippable;
	}

	bool Play(int flags)
	{
		mFlags = flags;
		return mIsPlaying = true;
	}

	bool Stop()
	{
		mCurrentFrameNumber = 0;
		return mIsPlaying = false;
	}

	EventFeed mFeed;
protected:

	FrameSet* mFrameSet;
	int mCurrentFrameNumber;
	Frame mCurrentFrame;
	int mTimer;
	int mFrameRate;
	bool mIsFlippable;
	bool mIsPlaying;
	int mFlags;		//LOOP, ONCE
	int mID;		//#define name eg. IDLE
};

class AnimDataPack
{
public:
	AnimDataPack() : mIndexer(), mAnimData() {}

	AnimDataPack(int AnimCount, FrameSet* AnimData, int* Index);

	FrameSet* GetAnimationData(int AnimationID);

	int GetAnimCount()
	{
		return mAnimCount;
	}

	int GetIndex(int i)
	{
		return mIndexer[i];
	}

	int GetFrameH()
	{
		return mAnimData->GetFrameRect(0).h;
	}

	int GetFrameW()
	{
		return mAnimData->GetFrameRect(0).w;
	}

	//For the loader
	void SetColData(int off_x, int off_y, int col_h, int col_w)
	{
		moff_x = off_x;
		moff_y = off_y;
		mcol_h = col_h;
		mcol_w = col_w;
	}

	int GetOff_x()
	{
		return moff_x;
	}

	int GetOff_y()
	{
		return moff_y;
	}

	int GetCol_h()
	{
		return mcol_h;
	}

	int GetCol_w()
	{
		return mcol_w;
	}

protected:

	int		    mAnimCount;
	int*        mIndexer;
	FrameSet*   mAnimData;


	int moff_x;
	int moff_y;
	int mcol_h;
	int mcol_w;
};

class AnimPack
{
public:
	AnimPack()  {}

	AnimPack(AnimDataPack* data);

	animation* ActivateAnimation(int AnimationID, int loop = LOOP); //Returns a pointer to an animation, starts it playing and stops the previous animation

	animation* GetAnimation(int AnimationID) //Just returns an animation pointer given an ID
	{
		for (int i = 0; i < mData->GetAnimCount(); i++)
		{
			if (mData->GetIndex(i) == AnimationID)
			{
				return &mAnims[i];
			}
		}
		gCons->ConsPrintf("Failed to get animation\n");
		return NULL;
	}

	AnimDataPack* GetAnimData()
	{
		return mData;
	}

	animation* GetAnimationDirect(int i)
	{
		return &mAnims[i];
	}

protected:

	AnimDataPack* mData;
	int			  mLastIndex;
	animation*    mAnims;

};

bool FrameCompare(Frame f1, Frame f2);

#endif