#ifndef ACTOR_H
#define ACTOR_H

#include "Utils.h"
#include "Console.h"
#include "Animation.h"
#include "AnimationGraph.h"
#include "Physics.h"
#include "Terrain.h"
//#include "ActorHandle.h"

#define SPLASH	   90

#define RUN_LEFT  0x1
#define RUN_RIGHT 0x02
#define RUN_DOWN  0x003
#define RUN_UP    0x0004
//

struct Trajectory
{
	float slope;
	int dir;
};

class ActorHandleManager;
class SpatialMonitor;

//consider making a lower level class for objects that have position and animate but don't interact with environment or other objects

class Actor : public EventReceiver
{
public:

	Actor() : mOpacity(255) {}

	Actor(AnimGraph* AnimData, SDL_Rect Pos, SDL_Rect DrawPos, ActorHandleManager* AHM, SpatialMonitor* spat, EventReceiver* prtLib, EventReceiver* SoundLib);

	virtual bool UpdateAnimation() = 0;

	virtual bool ActorUpdate() = 0;

	int GetX()
	{
		return mPosData.x;
	}

	int GetY()
	{
		return mPosData.y;
	}

	int GetHeight()
	{
		return mPosData.h;
	}

	int GetWidth()
	{
		return mPosData.w;
	}

	int GetDrawX()
	{
		return mDrawPos.x;
	}

	int GetDrawY()
	{
		return mDrawPos.y;
	}

	int GetDrawHeight()
	{
		return mDrawPos.h;
	}

	int GetDrawWidth()
	{
		return mDrawPos.w;
	}

	SDL_Rect* GetPosition()
	{
		return &mPosData;
	}

	SDL_Rect* GetDrawPosition()
	{
		return &mDrawPos;
	}

	SDL_Rect CalcDrawRect()
	{
		mDrawPos.h = mFrame->FrameRect.h;
		mDrawPos.w = mFrame->FrameRect.w;
		if (mDir == RIGHT)
		{
			mDrawPos.x = mOff_x;
		}
		else //mDir = LEFT
		{
			mDrawPos.x = -(mDrawPos.w + (mOff_x - mPosData.w) );
		}
		return mDrawPos;
	}

	int GetOpacity()
	{
		return mOpacity;
	}

	int SetOpacity(int i)
	{
		return mOpacity = i;
	}

	Frame* GetFrame()
	{
		return mFrame;
	}

	int GetState()
	{
		return mState;
	}

	int GetDir()
	{
		return mDir;
	}

	BinaryTree* GetHats()
	{
		return &mHats;
	}

	int AttachHat(Actor* hat)
	{
		mHats.Insert(hat->GetHandle(), hat);
		return hat->GetHandle();
	}

	int SetHandle(int i)
	{
		return mHandle = i;
	}

	int GetHandle()
	{
		return mHandle;
	}

	int SetSpatCell(int i)
	{
		return mSpatCell = i;
	}

	int GetSpatCell ()
	{
		return mSpatCell;
	}

	AnimGraph* GetAnimGraph()
	{
		return mAnimGraph;
	}

	void PassAnimGraphState()
	{
		mAnimGraph->GiveActorState(&mAnimID);
	}

	int GetAnimID()
	{
		return mAnimID;
	}

	int GetChannel()
	{
		return mSoundChannel;
	}

	bool IsBlocking()
	{
		return mBlocking;
	}

	EventFeed mFeed;

protected:

	AnimGraph* mAnimGraph;
	Frame* mFrame;
	int mOpacity;

	int mState;
	int mDir;
	int mAnimID;

	SDL_Rect mPosData; //Where the actors collision box is
	SDL_Rect mDrawPos; //Where the actor is drawn relative to its physical position (mPosData)
	
	int mOff_x;
	int mOff_y;

	BinaryTree mHats;

	ActorHandleManager* mAHM;
	int mHandle;

	SpatialMonitor* mSpat; //SpatialMonitor deals with actor collision and other region checking (like LoS)
	int mSpatCell;

	EventReceiver* mParticleLib; //Deals with the spawning of particles

	EventReceiver* mSoundLib;	//Deals with sounds and the spawning of point sounds
	int mSoundChannel; //used to play sounds directly from the actor

	bool mBlocking; //determines if an actor blocks other actors from passing through it
};

class Winch : public Actor
{
public:
	Winch(AnimGraph* AnimData, SDL_Rect Pos, SDL_Rect DrawPos, ActorHandleManager* AHM, SpatialMonitor* spat, EventReceiver* prtLib, EventReceiver* SoundLib, Actor* gate, int dir) : Actor(AnimData, Pos, DrawPos, AHM, spat, prtLib, SoundLib), mGate(gate)
	{
		mState = IDLE;
		mDir = dir;
	}

	bool EventProcess(Event eve);

	bool UpdateAnimation();

	bool ActorUpdate();

protected:

	Actor* mGate;
};

class Blocker : public Actor
{
public:
	Blocker(AnimGraph* AnimData, SDL_Rect Pos, SDL_Rect DrawPos, ActorHandleManager* AHM, SpatialMonitor* spat, EventReceiver* prtLib, EventReceiver* SoundLib);

protected:
};

class Test_Blocker : public Blocker
{
public:
	Test_Blocker(AnimGraph* AnimData, SDL_Rect Pos, SDL_Rect DrawPos, ActorHandleManager* AHM, SpatialMonitor* spat, EventReceiver* prtLib, EventReceiver* SoundLib);

	bool EventProcess(Event eve);

	bool UpdateAnimation();

	bool ActorUpdate();
protected:
};

class Gate : public Blocker
{
public:
	Gate(AnimGraph* AnimData, SDL_Rect Pos, SDL_Rect DrawPos, ActorHandleManager* AHM, SpatialMonitor* spat, EventReceiver* prtLib, EventReceiver* SoundLib, int dir = RIGHT);

	bool EventProcess(Event eve);

	bool UpdateAnimation();

	bool ActorUpdate();
protected:
};

class Interactable : public Actor
{
public:

	Interactable(AnimGraph* AnimData, SDL_Rect Pos, SDL_Rect DrawPos, ActorHandleManager* AHM, SpatialMonitor* spat, EventReceiver* prtLib, EventReceiver* SoundLib);

protected:
};

class Talker : public Interactable
{
public:
	Talker(AnimGraph* AnimData, SDL_Rect Pos, SDL_Rect DrawPos, ActorHandleManager* AHM, SpatialMonitor* spat, EventReceiver* prtLib, EventReceiver* SoundLib, char* str) : Interactable(AnimData, Pos, DrawPos, AHM, spat, prtLib, SoundLib), mStr(str)
	{}
	
	bool EventProcess(Event eve);

	bool UpdateAnimation();

	bool ActorUpdate();

protected:

	char* mStr;
};

class Gateman : public Talker
{
public:

	//Gateman(AnimGraph* AnimData, SDL_Rect Pos, SDL_Rect DrawPos, ActorHandleManager* AHM, SpatialMonitor* spat, EventReceiver* prtLib, EventReceiver* SoundLib, char* str, EventReceiver* gate) : Talker(AnimData, Pos, DrawPos, AHM, spat, prtLib, SoundLib, str), mGate(gate)
	Gateman(AnimGraph* AnimData, SDL_Rect Pos, SDL_Rect DrawPos, ActorHandleManager* AHM, SpatialMonitor* spat, EventReceiver* prtLib, EventReceiver* SoundLib, char* str, int gate);

	bool EventProcess(Event eve);

	bool UpdateAnimation();

	bool ActorUpdate();

protected:

	SDL_Rect mLOS;

	int mGateH; //handle for paired gate

	bool mTalked;
};

class Door : public Interactable
{
public:

	Door(AnimGraph* AnimData, SDL_Rect Pos, SDL_Rect DrawPos, ActorHandleManager* AHM, SpatialMonitor* spat, EventReceiver* prtLib, EventReceiver* SoundLib, int x_off, int y_off) : Interactable(AnimData, Pos, DrawPos, AHM, spat, prtLib, SoundLib)
	{
		mTele_Pos = mPosData;
		mTele_Pos.x += x_off;
		mTele_Pos.y += y_off;
	}

	SDL_Rect* GetTelePos()
	{
		return &mTele_Pos;
	}

	void SetTeleDest(SDL_Rect* dest)
	{
		mTele_Dest = dest;
	}

	bool EventProcess(Event eve);

	bool UpdateAnimation();

	bool ActorUpdate();

protected:

	SDL_Rect mTele_Pos;
	SDL_Rect* mTele_Dest;
};

class Mobile : public Actor
{
public:

	Mobile() : mXspd(0), mYspd(0) {}

	Mobile(AnimGraph* AnimData, SDL_Rect Pos, SDL_Rect DrawPos, ActorHandleManager* AHM, SpatialMonitor* spat, EventReceiver* prtLib, EventReceiver* SoundLib);
	
	void SetPosition(SDL_Rect* Dest);

	//bool ModifyActorPosition(int x, int y);

	SDL_Rect MoveActor(int xspd, int yspd);

	int MoveActorDirect(float xspd, float yspd);

protected:
	float mXspd;
	float mYspd;
	int mXmove;
	int mYmove;
};

class Hat : public Mobile
{
public:
	Hat(AnimGraph* AnimData, Actor* tar, ActorHandleManager* AHM, SpatialMonitor* spat, EventReceiver* prtLib, EventReceiver* SoundLib) : mTarget(tar), Mobile(AnimData, *tar->GetPosition(), *tar->GetDrawPosition(), AHM, spat, prtLib, SoundLib)
	{
		mEnabled = true;
	}

	bool IsEnabled()
	{
		return mEnabled;
	}

	void ToggleHat(bool state)
	{
		mEnabled = state;
	}

	bool EventProcess(Event eve)
	{
		return true;
	}

	bool ActorUpdate();

protected:

	Actor* mTarget;
	bool mEnabled;
};

class bad_hat : public Hat
{
public:
	
	bad_hat(AnimGraph* AnimData, Actor* tar, ActorHandleManager* AHM, SpatialMonitor* spat, EventReceiver* prtLib, EventReceiver* SoundLib) : Hat(AnimData, tar, AHM, spat, prtLib, SoundLib)
	{
	}

	bool UpdateAnimation()
	{
		switch (mState)
		{
		case RUN:
		default:
			mAnimID = IDLE;
			break;
		}
		mFrame = mAnimGraph->UpdateAnimation();
		return false;
	}
protected:
};

class sword : public Hat
{
public:

	sword(AnimGraph* AnimData, Actor* tar, ActorHandleManager* AHM, SpatialMonitor* spat, EventReceiver* prtLib, EventReceiver* SoundLib) : Hat(AnimData, tar, AHM, spat, prtLib, SoundLib)
	{
		mEnabled = true;
	}

	bool UpdateAnimation()
	{
		mAnimID = mTarget->GetAnimID();
		mFrame = mAnimGraph->UpdateAnimation();
		mDrawPos.h = mFrame->FrameRect.h;
		mDrawPos.w = mFrame->FrameRect.w;

		return false;
	}
protected:
};

class Character : public Mobile
{
public:

	Character() {}

	Character(SDL_Surface* ter, AnimGraph* AnimData, SDL_Rect Pos, SDL_Rect DrawPos, ActorHandleManager* AHM, SpatialMonitor* spat, EventReceiver* prtLib, EventReceiver* SoundLib);

	bool DetectFalling();

	bool UpdatePhysics();

	bool UpdateFireables();

	Trajectory GetTrajectory(SDL_Rect Dest, SDL_Rect Init);

	SDL_Rect RefinePosition(SDL_Rect* Dest, Trajectory trj, float destx, float desty, int RecursionCount = 0);

	bool HandleDirectionalCollisions(SDL_Rect& Destination);

	bool UpdatePosition();

	TerrainCollisionManager* getColMan()
	{
		return &mColMan;
	}

protected:

	SDL_Rect mDestData;
	colman_Character mColMan;
	PhysicsManager mPhysMan;
};

class Player : public Character
{
public:
	Player() {}

	Player(SDL_Surface* ter, AnimGraph* AnimData, SDL_Rect Pos, SDL_Rect DrawPos, ActorHandleManager* AHM, SpatialMonitor* spat, EventReceiver* prtLib, EventReceiver* SoundLib);

	bool EventProcess(Event eve);

	bool UpdateAnimation();

	bool ActorUpdate();

	int* GetHP()
	{
		return &mHP;
	}

	int* GetMaxHP()
	{
		return &mHPmax;
	}

	void SetSword(int index)
	{
		mHatIndex_Sword = index;
	}

protected:

//	bool mTalking;
	int mTalkerID;

	bool mWielded;
	int mHatIndex_Sword;

	//HP module
	int mHP;
	int mHPmax;
	int mHPtimer;
	//

	//blink module
	//int mBlinkDuration;
	//int mBlinkPeriod;
	//

	SDL_Rect mAttackZone;

	int mTimer;

	int mRecover; //Timer to force recovery pause between jumps

	SDL_Rect mTouch; //Rect that deterimes what can be interacted with
};

class Sludge_Seal : public Character
{
public:

	Sludge_Seal(SDL_Surface* ter, AnimGraph* AnimData, SDL_Rect Pos, SDL_Rect DrawPos, ActorHandleManager* AHM, SpatialMonitor* spat, EventReceiver* prtLib, EventReceiver* SoundLib) : Character(ter, AnimData, Pos, DrawPos, AHM, spat, prtLib, SoundLib), mDamagedTimer(0), mWanderLimit(0), mWanderTimer(0)
	{
		mState = IDLE;
		
		mTarget = -1;

		mLOS = mPosData;
		mLOS.x -= (170 - mLOS.w) / 2;
		mLOS.w = 170;

		mHPmax = 30;
		mHP = mHPmax;

		mDamage = 10;
	}

	bool Pursue();

	bool Wander();

	bool rest(int t);

	bool EventProcess(Event eve);

	virtual bool UpdateAnimation();

	bool ActorUpdate();

protected:

	int mTarget;
	int mRestTimer;
	SDL_Rect mLOS;

	int mHP;
	int mHPmax;
	int mDamage;

	int mDamagedTimer;

	int mWanderTimer;
	int mWanderLimit;
};

class Loyal_Bug : public Character
{
public:
	Loyal_Bug(SDL_Surface* ter, AnimGraph* AnimData, SDL_Rect Pos, SDL_Rect DrawPos, ActorHandleManager* AHM, SpatialMonitor* spat, EventReceiver* prtLib, EventReceiver* SoundLib) : mMounted(false), Character(ter, AnimData, Pos, DrawPos, AHM, spat, prtLib, SoundLib)
	{
	}

	bool EventProcess(Event eve);

	bool UpdateAnimation();

	bool ActorUpdate();

protected:

	bool mMounted;
};

class Bug : public Character
{
public:
	Bug(SDL_Surface* ter, AnimGraph* AnimData, SDL_Rect Pos, SDL_Rect DrawPos, ActorHandleManager* AHM, SpatialMonitor* spat, EventReceiver* prtLib, EventReceiver* SoundLib) : Character(ter, AnimData, Pos, DrawPos, AHM, spat, prtLib, SoundLib)
	{
	}

protected:

	int mTimer;

};

class Wanderer : public Character
{
public:

	Wanderer() : mWaitLimit(0), mWaitTimer(0), mWanderLimit(0), mWanderTimer(0) {}

	Wanderer(SDL_Surface* ter, AnimGraph* AnimData, SDL_Rect Pos, SDL_Rect DrawPos, ActorHandleManager* AHM, SpatialMonitor* spat, EventReceiver* prtLib, EventReceiver* SoundLib) : Character(ter, AnimData, Pos, DrawPos, AHM, spat, prtLib, SoundLib), mWanderTimer(0), mWanderLimit(0), mWaitTimer(0), mWaitLimit(0)
	{
	}

	bool Wander();

	bool WaitRandom();

	bool EventProcess(Event eve);

	virtual bool UpdateAnimation();

	bool ActorUpdate();

protected:

	int mWanderTimer;
	int mWanderLimit;
	int mWaitLimit;
	int mWaitTimer;
};

class Pursuer : public Character
{
public:
	Pursuer() {}

	Pursuer(SDL_Surface* ter, AnimGraph* AnimData, SDL_Rect Pos, SDL_Rect DrawPos, ActorHandleManager* AHM, SpatialMonitor* spat, EventReceiver* prtLib, EventReceiver* SoundLib) : Character(ter, AnimData, Pos, DrawPos, AHM, spat, prtLib, SoundLib), mRestTimer(0)
	{
		mState = IDLE;
		mLOS = mPosData;
		mLOS.x -= (170 - mLOS.w) / 2;
		mLOS.w = 170;
	}

	bool Pursue();

	bool rest(int t);

	bool EventProcess(Event eve);

	virtual bool UpdateAnimation();

	bool ActorUpdate();

protected:

	Actor* mTarget;
	int mRestTimer;
	SDL_Rect mLOS;
};

class Rabbit : public Character
{
public:
	Rabbit() {}

	Rabbit(SDL_Surface* ter, AnimGraph* AnimData, SDL_Rect Pos, SDL_Rect DrawPos, ActorHandleManager* AHM, SpatialMonitor* spat, EventReceiver* prtLib, EventReceiver* SoundLib) : Character(ter, AnimData, Pos, DrawPos, AHM, spat, prtLib, SoundLib), mWaitLimit(0), mWaitTimer(0), mWanderLimit(0), mWanderTimer(0)
	{
	}

	bool Hop();

	bool Wander();

	bool Behave();

	bool WaitRandom();

	bool EventProcess(Event eve);

	virtual bool UpdateAnimation();

	bool ActorUpdate();

protected:

	int mWanderTimer;
	int mWanderLimit;
	int mWaitLimit;
	int mWaitTimer;
};

#endif