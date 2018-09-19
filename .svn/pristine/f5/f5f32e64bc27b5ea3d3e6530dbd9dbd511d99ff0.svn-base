#include "Actor.h"
#include "DiagnosticDraw.h"
#include "ActorHandle.h"
#include "ActorCollision.h"

Actor::Actor(AnimGraph* AnimData, SDL_Rect Pos, SDL_Rect DrawPos, ActorHandleManager* AHM, SpatialMonitor* spat, EventReceiver* prtLib, EventReceiver* SoundLib) : mSpatCell(-1)
{
	mAnimGraph = AnimData;
	mPosData = Pos;
	mDrawPos = DrawPos;

	mOff_x = DrawPos.x;
	mOff_y = DrawPos.y;

	mState = IDLE;

	mAHM = AHM;
	//if (AHM != NULL) { mHandle = AHM->EventProcess(Event(ASSIGN_HANDLE, (EventReceiver*)this)); } 
	if (mAHM != NULL) { mHandle = mAHM->AssignHandle(this); } //Get a unique handle from the AHM and register it with a pointer to yourself

	mSpat = spat;
	if (mSpat != NULL) { mSpat->LogActor(mHandle); } //Pass your handle to the collsion system.

	mParticleLib = prtLib;
	mSoundLib = SoundLib;

	mOpacity = 255;

	PassAnimGraphState(); //Link the actor AnimState to the animgraph

	mSoundChannel = -1;
	if (mSoundLib != NULL)
	{
		mSoundLib->EventProcess(Event(SPAWN, (void*)&mSoundChannel));
#ifdef DEBUG
		assert(mSoundChannel != -1);
#endif // DEBUG
	}

	mBlocking = false;
}

//Winch
bool Winch::EventProcess(Event eve)
{
	switch (*eve.GetEventType())
	{
	case INTERACT:
		gCons->ConsPrintf("Winch received interact event\n");
		mFeed.EventProcess(Event(SWITCH));
		break;
	default:
//		gCons->ConsPrintf("Winch received unrecognized event\n");
		return false;
		break;
	}
	return true;
}

bool Winch::UpdateAnimation()
{
	mAnimID = mGate->GetAnimID();
	mFrame = mAnimGraph->UpdateAnimation();
	return false;
}

bool Winch::ActorUpdate()
{
	//gDiagDraw->LogDiagRect(mPosData);
	UpdateAnimation();
	return false;
}
//

//Blocker
Blocker::Blocker(AnimGraph* AnimData, SDL_Rect Pos, SDL_Rect DrawPos, ActorHandleManager* AHM, SpatialMonitor* spat, EventReceiver* prtLib, EventReceiver* SoundLib) : Actor(AnimData, Pos, DrawPos, AHM, spat, prtLib, SoundLib)
{
}
//

//Test_Blocker
Test_Blocker::Test_Blocker(AnimGraph* AnimData, SDL_Rect Pos, SDL_Rect DrawPos, ActorHandleManager* AHM, SpatialMonitor* spat, EventReceiver* prtLib, EventReceiver* SoundLib) : Blocker(AnimData, Pos, DrawPos, AHM, spat, prtLib, SoundLib)
{
	mState = IDLE;
	mAnimID = IDLE;
	mBlocking = true;
}

bool Test_Blocker::EventProcess(Event eve)
{
	switch (*eve.GetEventType())
	{
	case INTERACT:
		mBlocking = !mBlocking;
		gCons->ConsPrintf("Blocker received interact event\n");
		break;
	default:
		gCons->ConsPrintf("Blocker received unrecognized event\n");
		return false;
		break;
	}
	return true;
}

bool Test_Blocker::UpdateAnimation()
{
	mFrame = mAnimGraph->UpdateAnimation();
	return false;
}

bool Test_Blocker::ActorUpdate()
{
	//gDiagDraw->LogDiagRect(mPosData);
	UpdateAnimation();
	return false;
}
//

//Gate functions
Gate::Gate(AnimGraph* AnimData, SDL_Rect Pos, SDL_Rect DrawPos, ActorHandleManager* AHM, SpatialMonitor* spat, EventReceiver* prtLib, EventReceiver* SoundLib, int dir) : Blocker(AnimData, Pos, DrawPos, AHM, spat, prtLib, SoundLib)
{
	mState = GATE_DOWN;
	mBlocking = true;
	mDir = dir;
}

bool Gate::EventProcess(Event eve)
{
	switch (*eve.GetEventType())
	{
	case SWITCH:
		//mBlocking = !mBlocking;
		if (mState == GATE_DOWN ) { mState = GATE_RAISE;   }
		if (mState == GATE_UP   ) { mState = GATE_LOWER; mBlocking = true; }
		//gCons->ConsPrintf("Gate received interact event\n");
		break;
	case ANIM_COMPLETE:
		switch (eve.GetEventData()->i)
		{
		case GATE_RAISE:
			mBlocking = false;
			mState = GATE_UP;
			break;
		case GATE_LOWER:
			mState = GATE_DOWN;
			break;
		default:
			break;
		}
	default:
		//gCons->ConsPrintf("Gate received unrecognized event\n");
		return false;
		break;
	}
	return true;
}

bool Gate::UpdateAnimation()
{
	switch (mState)
	{
	case GATE_LOWER:
	case GATE_DOWN:
		mAnimID = GATE_DOWN;
		break;
	case GATE_RAISE:
	case GATE_UP:
		mAnimID = GATE_UP;
		break;
	default:
		break;
	}
	mFrame = mAnimGraph->UpdateAnimation();
	return false;
}

bool Gate::ActorUpdate()
{
	//gDiagDraw->LogDiagRect(mPosData);
	UpdateAnimation();
	return false;
}
//
//

//Interactable Functions
Interactable::Interactable(AnimGraph* AnimData, SDL_Rect Pos, SDL_Rect DrawPos, ActorHandleManager* AHM, SpatialMonitor* spat, EventReceiver* prtLib, EventReceiver* SoundLib) : Actor(AnimData, Pos, DrawPos, AHM, spat, prtLib, SoundLib)
{
	mState = IDLE;
	mAnimID = IDLE;
}

//Talker
bool Talker::EventProcess(Event eve)
{
	switch (*eve.GetEventType())
	{
	case INTERACT:
		mAHM->GetActorAddress(eve.GetEventData()->i)->EventProcess(Event(DIALOGUE, mStr, mHandle));
		//gCons->ConsPrintf("Talker received interact event\n");
		break;
	case TERMINATE_DIALOGUE:
		break;
	default:
		gCons->ConsPrintf("Talker received unrecognized event\n");
		return false;
		break;
	}
	return true;
}

bool Talker::UpdateAnimation()
{
	mFrame = mAnimGraph->UpdateAnimation();
	return false;
}

bool Talker::ActorUpdate()
{
	//gDiagDraw->LogDiagRect(mPosData);
	UpdateAnimation();
	return false;
}
//

//GateMan
Gateman::Gateman(AnimGraph* AnimData, SDL_Rect Pos, SDL_Rect DrawPos, ActorHandleManager* AHM, SpatialMonitor* spat, EventReceiver* prtLib, EventReceiver* SoundLib, char* str, int gate) : Talker(AnimData, Pos, DrawPos, AHM, spat, prtLib, SoundLib, str), mGateH(gate)
{
	mLOS = Pos;
	mLOS.w = 150;
	mLOS.x = mLOS.x - 75 - (int)((float)mPosData.w / 2);//(mLOS.x - (30 - (mPosData.w) / 2));
	mLOS.h = 70;

	mTalked = false;
	mState = GATE_DOWN;

	mDir = mAHM->GetActorAddress(mGateH)->GetDir();
}


bool Gateman::EventProcess(Event eve)
{
	switch (*eve.GetEventType())
	{
	case INTERACT:
		//mAHM->GetActorAddress(eve.GetEventData()->i)->EventProcess(Event(DIALOGUE, mStr, mHandle));
		//gCons->ConsPrintf("Talker received interact event\n");
		break;
	case SENSOR_COLLISION:
		switch (eve.GetEventData()->sr.st)
		{
		case LOS:
			//((EventReceiver*)(eve.GetEventData()->sr.er))->EventProcess(Event(PLAYER_CHECK, *eve.GetEventData(), this));
			(mAHM->GetActorAddress(eve.GetEventData()->sr.id))->EventProcess(Event(PLAYER_CHECK, *eve.GetEventData(), mHandle));
			break;
		default:
			break;
		}
		break;
	case PLAYER_CONFIRM:
		(mAHM->GetActorAddress(eve.GetEventData()->sr.id))->EventProcess(Event(DIALOGUE, mStr, mHandle));
		break;
	case TERMINATE_DIALOGUE:
		if (mTalked == false)
		{
			//mGate->EventProcess(Event(INTERACT));
			((ActorHandleManager*)mAHM)->GetActorAddress(mGateH)->EventProcess(Event(INTERACT));
			//( mAHM->EventProcess(Event(GET_ACTOR_ADDRESS, mGateH)) ).EventProcess(Event(INTERACT)); //Event process can only return bools. Might change later.
			mState = GATE_UP;
			mTalked = true;
		}
		//open the gate
		break;
	default:
		gCons->ConsPrintf("Gateman received unrecognized event\n");
		return false;
		break;
	}
	return true;
}

bool Gateman::UpdateAnimation()
{
	switch (mState)
	{
	case IDLE:
		mAnimID = IDLE;
		mFrame = mAnimGraph->UpdateAnimation();
		break;
	case GATE_UP:
		mAnimID = GATE_UP;
		mFrame = mAnimGraph->UpdateAnimation();
		break;
	case GATE_DOWN:
		mAnimID = GATE_DOWN;
		mFrame = mAnimGraph->UpdateAnimation();
		break;
	}
	return false;
}

bool Gateman::ActorUpdate()
{
	//gDiagDraw->LogDiagRect(mPosData);
	gDiagDraw->LogDiagRect(mLOS);
	if (mTalked == false)
	{
		mSpat->EventProcess(Event(CHECK_RECT_SENSOR, LOS, &mLOS, mHandle));
	}
	UpdateAnimation();
	return false;
}
//

//Door
bool Door::EventProcess(Event eve)
{
	switch (*eve.GetEventType())
	{
	case INTERACT:
		mAHM->GetActorAddress(eve.GetEventData()->i)->EventProcess(Event(TELEPORT, mTele_Dest));
		gCons->ConsPrintf("Door received interact event\n");
		break;
	default:
		gCons->ConsPrintf("Door received unrecognized event\n");
		return false;
		break;
	}
	return true;
}

bool Door::UpdateAnimation()
{
	mFrame = mAnimGraph->UpdateAnimation();
	return false;
}

bool Door::ActorUpdate()
{
	//gDiagDraw->LogDiagRect(mPosData);
	//gDiagDraw->LogDiagRect(mTele_Pos);
	UpdateAnimation();
	return false;
}
//

//Mobile Functions
Mobile::Mobile(AnimGraph* AnimData, SDL_Rect Pos, SDL_Rect DrawPos, ActorHandleManager* AHM, SpatialMonitor* spat, EventReceiver* prtLib, EventReceiver* SoundLib) : Actor(AnimData, Pos, DrawPos, AHM, spat, prtLib, SoundLib), mXmove(0), mYmove(0), mXspd(0), mYspd(0)
{
}

void Mobile::SetPosition(SDL_Rect* Dest)
{
	//mPosData = *Dest;
	mPosData.x = Dest->x;
	mPosData.y = Dest->y;
//	CalcDrawRect();
//	mSpat->EventProcess(Event(MOVED_THIS_FRAME, mHandle));
}

//bool Mobile::ModifyActorPosition(int x, int y)
//{
//	mPosData.x = x + mPosData.x;
//	mPosData.y = y + mPosData.y;
//	mDrawPos = mPosData;
//	return false;
//}

SDL_Rect Mobile::MoveActor(int xspd, int yspd)
{
	SDL_Rect Delta;
	Delta.h = 0;
	Delta.w = 0;
	Delta.x = xspd;
	Delta.y = yspd;

	return Delta;
}

int Mobile::MoveActorDirect(float xspd, float yspd)
{
	mPosData.x = mPosData.x + (int)(xspd);
	mPosData.y = mPosData.y + (int)(yspd);
	return 0;
}

//Hat
bool Hat::ActorUpdate()
{
	mState = mTarget->GetState();
	mDir = mTarget->GetDir();
	UpdateAnimation();
	SetPosition(mTarget->GetPosition());
	CalcDrawRect();
	SDL_Rect debug_draw = mDrawPos;
	debug_draw.x += mPosData.x;
	debug_draw.y += mPosData.y;
	//gDiagDraw->LogDiagRect(debug_draw);
	//gDiagDraw->LogDiagRect(mDrawPos);
	return true;
}
//

//Character Functions
Character::Character(SDL_Surface* ter, AnimGraph* AnimData, SDL_Rect Pos, SDL_Rect DrawPos, ActorHandleManager* AHM, SpatialMonitor* spat, EventReceiver* prtLib, EventReceiver* SoundLib) : Mobile(AnimData, Pos, DrawPos, AHM, spat, prtLib, SoundLib ) , mColMan(ter, &mPosData, &mDestData, 5), mPhysMan(0.5, (float)0.08, &mPosData.y, &mXspd, &mYspd), mDestData(mPosData)
{
}

bool Character::DetectFalling()
{
	SDL_Rect GroundDetector = mPosData;
	GroundDetector.y = (mPosData.y + mPosData.h);
	GroundDetector.h = 1;
	if (mColMan.DetectFalling() == true && (mSpat->EventProcess(Event(CHECK_BLOCKERS, Touch, &GroundDetector, mHandle)) == false))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Character::UpdatePhysics()
{
	if (DetectFalling() == false)
	{
		mPhysMan.SetGravity(false);
	}
	else
	{
		mPhysMan.SetGravity(true);
	}

	if (mColMan.DetectSurface() == true)
	{
		mPhysMan.ZeroBouyantSurface();
	}

	if (mColMan.DetectSwim() == true)
	{
		mPhysMan.SetFloating(true);
		mPhysMan.SetGravity(false);

		if (mYmove > 0)
		{
			mPhysMan.SetFloating(false);
		}
	}
	else
	{
		mPhysMan.SetFloating(false);
	}
	
	return mPhysMan.ApplyPhysics();
}

bool Character::UpdateFireables()
{
	if (mColMan.DetectSwim() == false)
	{
		int y = mColMan.FindSurface();
		if (mColMan.DetectWade())
		{
			if (FrameCompare(*mFrame, mAnimGraph->GetAnimPack()->GetAnimation(RUN)->GetFrame(5)) || FrameCompare(*mFrame, mAnimGraph->GetAnimPack()->GetAnimation(RUN)->GetFrame(13)))
			{
				if (mDir == LEFT)
				{
					mParticleLib->EventProcess(Event(CREATE_PARTICLE, "P_static", "splash", mPosData.x + mDrawPos.x + 2 - 10, y - 3));
					mSoundLib->EventProcess(Event(CREATE_POINT_SOUND, NULL, "splash_sound", mPosData.x + mDrawPos.x + 2 - 10, y - 3)); //type field "NULL", unused for sound. will be used if sounds have types
				}
				else
				{
					mParticleLib->EventProcess(Event(CREATE_PARTICLE, "P_static", "splash", mPosData.x + mDrawPos.x + 12 - 10, y - 3));
					mSoundLib->EventProcess(Event(CREATE_POINT_SOUND, NULL, "splash_sound", mPosData.x + mDrawPos.x + 12 - 10, y - 3));
				}
			}
			if (FrameCompare(*mFrame, mAnimGraph->GetAnimPack()->GetAnimation(IDLE_BEGIN)->GetFrame(1)) || DetectFalling())
			{
				mParticleLib->EventProcess(Event(CREATE_PARTICLE, "P_static", "splash", mPosData.x + mDrawPos.x + 2 - 10, y - 3));
				mParticleLib->EventProcess(Event(CREATE_PARTICLE, "P_static", "splash", mPosData.x + mDrawPos.x + 12 -10, y - 3));
				mSoundLib->EventProcess(Event(CREATE_POINT_SOUND, NULL, "splash_sound", mPosData.x + mDrawPos.x + 2, y - 3));
			}
		}

		if (DetectFalling() == false)
		{
			if (FrameCompare(*mFrame, mAnimGraph->GetAnimPack()->GetAnimation(RUN)->GetFrame(5)) || FrameCompare(*mFrame, mAnimGraph->GetAnimPack()->GetAnimation(RUN)->GetFrame(13)))
			{
				if (mDir == LEFT)
				{
					mSoundLib->EventProcess(Event(CREATE_POINT_SOUND, NULL, "footstep", mPosData.x + mDrawPos.x + 2 - 10, mPosData.y + 22));
				}
				else //RIGHT
				{
					mSoundLib->EventProcess(Event(CREATE_POINT_SOUND, NULL, "footstep", mPosData.x + mDrawPos.x + 12 -10, mPosData.y + 22));
				}
			}
			if (FrameCompare(*mFrame, mAnimGraph->GetAnimPack()->GetAnimation(RUN_DRAWN)->GetFrame(5)) || FrameCompare(*mFrame, mAnimGraph->GetAnimPack()->GetAnimation(RUN_DRAWN)->GetFrame(13)))
			{
				if (mDir == LEFT)
				{
					mSoundLib->EventProcess(Event(CREATE_POINT_SOUND, NULL, "footstep", mPosData.x + mDrawPos.x + 2 - 10, mPosData.y + 22));
				}
				else //RIGHT
				{
					mSoundLib->EventProcess(Event(CREATE_POINT_SOUND, NULL, "footstep", mPosData.x + mDrawPos.x + 12 - 10, mPosData.y + 22));
				}
			}
		}
	}
	return true;
}

Trajectory Character::GetTrajectory(SDL_Rect Dest, SDL_Rect Init)
{
	float xdelt = (float)(-Init.x + Dest.x);
	float ydelt = (float)(-Init.y + Dest.y);

	Trajectory trj;

	if (xdelt == 0)
	{
		trj.dir = 0; //flag for vertical/undefined trajectory

		if (ydelt > 0)
		{
			trj.slope = 1;
		}
		if (ydelt < 0)
		{
			trj.slope = -1;
		}
		if (ydelt == 0)
		{
			trj.slope = 0;
		}
	}
	else
	{
		trj.slope = (ydelt / xdelt);

		//gCons->ConsPrintf("Traject = %f / %f\n", ydelt, xdelt);

		if (xdelt > 0)
		{
			trj.dir = 1;
		}
		if (xdelt < 0)
		{
			trj.dir = -1;
		}
	}
	return trj;
}

SDL_Rect Character::RefinePosition(SDL_Rect* Dest, Trajectory trj, float destx, float desty, int RecursionCount) //Shouldn't check fractional movement. Position cannot be fraction anyway. Lower of x/y whould be 1 other should be slope
{
	if ( (mColMan.DetectEdgeCollision(Dest) == true) || (mSpat->EventProcess(Event(CHECK_BLOCKERS, Touch, Dest, mHandle)) == true))
	{
		if (trj.dir == 0) //vertical trajectory
		{
			desty -= (trj.slope);
		}
		else
		{
			destx -= trj.dir;
			desty -= trj.dir*trj.slope;

			//gCons->ConsPrintf("Dest x: %i, Dest y: %i \n", Dest->x, Dest->y);
		}

		Dest->y = (int)desty;
		Dest->x = (int)destx;
		if (RecursionCount < 300) //this should probably be lower
		{
			RefinePosition(Dest, trj, destx, desty, (RecursionCount + 1));
		}
		else
		{
			gCons->ConsPrintf("Refine Position Recursion Limit Reached\n");
		}
	}
	return *Dest;
}

bool Character::HandleDirectionalCollisions(SDL_Rect& Destination)
{
	SDL_Rect l_bump = mPosData;
		l_bump.x -= 1;
		l_bump.w = 1;
		l_bump.h -= 4;
	SDL_Rect r_bump = mPosData;
		r_bump.x += r_bump.w;
		r_bump.w = 1;
		r_bump.h -= 4;
	if ( ((mColMan.DetectDirectionalCollision(&mPosData, LEFT) == true) || mSpat->EventProcess(Event(CHECK_BLOCKERS, Touch, &l_bump, mHandle))) && ((mXmove + mXspd) < 0))
	{
		Destination.x = mPosData.x;
		mXspd = 0;
		//mXmove = 0;
	}
	else if ( ((mColMan.DetectDirectionalCollision(&mPosData, RIGHT) == true) || mSpat->EventProcess(Event(CHECK_BLOCKERS, Touch, &r_bump, mHandle))) && ((mXmove + mXspd) > 0))
	{
		Destination.x = mPosData.x;
		mXspd = 0;
		//mXmove = 0;
	}
	else
	{
		Destination.x = mPosData.x + (int)mXspd + mXmove;
	}

	if ((mColMan.DetectDirectionalCollision(&mPosData, UP) == true) && ((mYmove + mYspd) < 0))
	{
		Destination.y = mPosData.y;
		mYspd = 0;
		//mYmove = 0;
	}
	else if ((mColMan.DetectDirectionalCollision(&mPosData, DOWN) == true) && ((mYmove + mYspd) > 0))
	{
		Destination.y = mPosData.y;
		mYspd = 0;
		//mYmove = 0;
	}
	else
	{
		Destination.y = mPosData.y + (int)mYspd + mYmove;
	}

	if ((mSpat->EventProcess(Event(CHECK_BLOCKERS, Touch, &mDestData, mHandle)) == true))
	{
		Destination.x = mPosData.x;
		mXspd = 0;
		Destination.y = mPosData.y;
		mYspd = 0;
	}
	return true;
}

bool Character::UpdatePosition()
{
	
	//(mSpat->EventProcess(Event(CHECK_BLOCKERS, Touch, &mDestData, mSpatID)) == true);
	//gCons->ConsPrintf("Blocker: %i\n", mSpat->EventProcess(Event(CHECK_BLOCKERS, Touch, &mDestData, mSpatID)));

	if (( (mYmove + mYspd) < 0) || (mYmove > 0)) //if you are moving up or actively moving down
	{
		mColMan.SetPlaformCollision(false);
	}
	else
	{
		mColMan.SetPlaformCollision(true);
	}

	HandleDirectionalCollisions(mDestData);

	if (mColMan.DetectEdgeCollision(&mDestData) == true )
	{
		if (int i = mColMan.DetectIncline(8) < 8) //8 == maximum climable step
		{
			if (mDestData.y == mPosData.y)
			{
				mDestData.y += -i;
				
			}
		}	
	}

	RefinePosition(&mDestData, GetTrajectory(mDestData, mPosData), (float)mDestData.x, (float)mDestData.y); //Redundant Args
	mColMan.SetPlaformCollision(true);

	if ( (mPosData.x != mDestData.x) || (mPosData.y != mDestData.y) )
	{
		
		SetPosition(&mDestData);
		//mPosData = mDestData;

		mSpat->EventProcess(Event(MOVED_THIS_FRAME, mHandle));
		return true;
	}
	else
	{
		return false;
	}
}

//Player Functions
Player::Player(SDL_Surface* ter, AnimGraph* AnimData, SDL_Rect Pos, SDL_Rect DrawPos, ActorHandleManager* AHM, SpatialMonitor* spat, EventReceiver* prtLib, EventReceiver* SoundLib) : mWielded(false), mTalkerID(-1), mHP(100), mHPmax(100), mHPtimer(0), mRecover(0), mTouch(Pos), mAttackZone(Pos), Character(ter, AnimData, Pos, DrawPos, AHM, spat, prtLib, SoundLib)
{
	mTouch.h = Pos.h;
	mTouch.w = 18;

	mAttackZone.w = 16;
	((sword*)(mAHM->GetActorAddress(mHatIndex_Sword)))->ToggleHat(true);
}

bool Player::EventProcess(Event eve)
{
	switch (*eve.GetEventType())
	{

	case ACTOR_COLLISION:
		//gCons->ConsPrintf("Player is intersecting another actor\n");
		break;
	case PLAYER_CHECK:
		mAHM->GetActorAddress(eve.GetReturnAddress())->EventProcess(Event(PLAYER_CONFIRM, *eve.GetEventData(), mHandle)); 
		break;
	case DIALOGUE:
	{
		mFeed.EventProcess(eve);	//Talkers pass dialogue events to the player who then passes them to the dialogue widget; Dialogue HUD widget is subscribed to the player and processes this event
		mTalkerID = eve.GetEventData()->dd.talkerID;
		mState = IDLE;
		break;						
	}
	case TERMINATE_DIALOGUE:
	{
		//mTalking = false;
		mAHM->GetActorAddress(mTalkerID)->EventProcess(eve);
		mTalkerID = -1;
		break;
	}
	case TELEPORT:
	{
		SetPosition(eve.GetEventData()->rect);
		mFeed.EventProcess(Event(FADE, 10, FADE_BLACK, 255)); //Trigger the fader
		mSoundLib->EventProcess(Event(CREATE_POINT_SOUND, NULL, "door_open", mPosData.x + mDrawPos.x + 5, mPosData.y + 12));
		gCons->ConsPrintf("actor x: %i, actor y: %i", mPosData.x, mPosData.y);
		break;
	}
	case SENSOR_COLLISION:
		switch (eve.GetEventData()->sr.st)
		{
		case Touch:
			(mAHM->GetActorAddress(eve.GetEventData()->sr.id))->EventProcess(Event(INTERACT, mHandle));
			break;
		case Attack:
			(mAHM->GetActorAddress(eve.GetEventData()->sr.id))->EventProcess(Event(DAMAGE, 10, mHandle));
			break;
		default:
			break;
		}
		break;

	case DAMAGE:
		mHP -= eve.GetEventData()->damd.damage;
		mHPtimer = 350;
		mFeed.EventProcess(Event(FADE, 10, FADE_RED, 50)); //Trigger the fader
		mSoundLib->EventProcess(Event(CREATE_POINT_SOUND, NULL, "ouch", mPosData.x + mDrawPos.x + 5, mPosData.y + 12));
		//mBlinkDuration = gTime->GetCurrentCycle();
		//mBlinkPeriod = gTime->GetCurrentCycle();
		//gCons->ConsPrintf("Player has received a damage event!\n");
		//gCons->ConsPrintf("Current hp is: %i\n", mHP);
		break;
	
	//Control Events
	case KEY_UP: //should be "no keys pressed" not released a key
		if (mState == ATTACK) { break; }
		switch (eve.GetEventData()->i)
		{
		case SDL_SCANCODE_LEFT:
		case SDL_SCANCODE_RIGHT:
		case SDL_SCANCODE_UP:
		case SDL_SCANCODE_SPACE:
		case SDL_SCANCODE_DOWN:
			if (mColMan.DetectSwim() == true)
			{
				mState = TREAD;
				break;
			}
			mState = IDLE;
			break;
		default:
			break;
		}
		break;
	case KEY_DOWN:
		if (mState == ATTACK) { break; }
		switch (eve.GetEventData()->i)
		{
		case SDL_SCANCODE_LEFT:
			if (mTalkerID != -1) { break; }
			mDir = LEFT;
			mState = RUN_LEFT;
			break;
		case SDL_SCANCODE_RIGHT:
			if (mTalkerID != -1) { break; }
			mDir = RIGHT;
			mState = RUN_RIGHT;
			break;
		case SDL_SCANCODE_UP:
		case SDL_SCANCODE_SPACE:
			if (mTalkerID != -1) { break; }
			if (mColMan.DetectSwim() == true)
			{
				mState = SWIM_UP;
				break;
			}
			mState = JUMP;
			break;
		case SDL_SCANCODE_DOWN: //this should be only allow when swimming like "SWIM_UP" but has some debugging utility for now
			if (mTalkerID != -1) { break; }
			if (mColMan.DetectSwim() == true)
			{
				mState = SWIM_DOWN;
				break;
			}
			mState = RUN_DOWN;
			break;
		case SDL_SCANCODE_E:
			if (mTalkerID != -1)
			{
				mFeed.EventProcess(Event(SCROLL)); //Dialogue HUD widget is subscribed to the player and processes this event
			}
			else
			{
				mSpat->EventProcess(Event(CHECK_RECT_SENSOR, Touch, &mTouch, mHandle));
			}
			break;
		case SDL_SCANCODE_Q:
			if (mTalkerID != -1) { break; }
			mWielded = !mWielded;
			mSoundLib->EventProcess(Event(CREATE_POINT_SOUND, NULL, "draw_sword", mPosData.x + mDrawPos.x + 5, mPosData.y + 12)); // Should this use mSoundChannel?
			break;	
		case SDL_SCANCODE_W:
			if (mTalkerID != -1 ) { break; }
			if (mWielded != true) { break; }
			mTimer = gTime->GetCurrentMS();
			if ((mState != JUMP) && (mState != FALL))
			{
				mXmove = 0;
			}
			mState = ATTACK;
			mSoundLib->EventProcess(Event(CREATE_POINT_SOUND, NULL, "player_attack", mPosData.x + mDrawPos.x + 5, mPosData.y + 12)); // Should this use mSoundChannel?
			mSpat->EventProcess(Event(CHECK_RECT_SENSOR, Attack, &mAttackZone, mHandle));
			break;
		default:
		gCons->ConsPrintf("Player asked to process unrecognized event\n");
		}
	}

	return false;
}

bool Player::UpdateAnimation()
{
	switch (mState)
	{
	case RUN_DOWN:
		break;
	case RUN_LEFT:
	case RUN_RIGHT:
		if (mColMan.DetectSwim() == true)
		{
			mAnimID = SWIM;
			break;
		}
		if (mWielded == true)
		{
			mAnimID = RUN_DRAWN;
		}
		else //mWielded == false
		{
			mAnimID = RUN;
		}
		break;
	case JUMP:
		if (mWielded == true)
		{
			mAnimID = JUMP_DRAWN;
		}
		else
		{
			mAnimID = JUMP;
		}
		break;
	case SWIM_UP:
		mAnimID = SWIM;
		break;
	case ATTACK:
		mAnimID = ATTACK;
		break;
	case IDLE:
	default:
		if (mWielded == true)
		{
			mAnimID = IDLE_DRAWN;
		}
		else
		{
			mAnimID = IDLE;
		}
		//break;
		if (mColMan.DetectSwim() == true) //overwrite previous logic if this condition is true
		{
			mAnimID = TREAD;
			break;
		}
	}
	if ( (mYspd > 0) && (DetectFalling() == true) && (mState != ATTACK) )
	{
		if (mWielded == true)
		{
			mAnimID = FALL_DRAWN;
		}
		else
		{
			mAnimID = FALL;
		}
	}
	mFrame = mAnimGraph->UpdateAnimation();
	CalcDrawRect();
	return true;
}

bool Player::ActorUpdate()
{
	if (mHP <= 0)
	{
		mFeed.EventProcess(Event(GAME_OVER));
		//game over
	}

	switch (mState)
	{
	case SWIM_DOWN:
	case RUN_DOWN:
		mYmove = 3;
		break;
	case SWIM_UP:
		mYmove = -6;
		break;
	case SWIM_RIGHT:
	case RUN_RIGHT:
		mXmove = 3;
		break;
	case SWIM_LEFT:
	case RUN_LEFT:
		mXmove = -3;
		break;
	case JUMP:
		if (DetectFalling() == false && ((gTime->GetCurrentCycle() - mRecover) > 14) ) //14 should be more like 3 mRecover is set correctly
		{
			mYspd = -7;
			mRecover = gTime->GetCurrentCycle(); //needs to get set when you land
		}
		break;
	case TREAD:
	case IDLE:
		mXmove = 0;
		mYmove = 0;
		break;
	case ATTACK:
		mSpat->EventProcess(Event(CHECK_RECT_SENSOR, Attack, &mAttackZone, mHandle));
		if (gTime->GetCurrentMS() - mTimer >= 600)
		{
			mState = IDLE;
		}
		//gCons->ConsPrintf("Player attacks!\n");
		break;
	default:
		gCons->ConsPrintf("Actor in invalid state\n");
		return false;
	}

	if ((mHPtimer == 0) && (mHP < mHPmax))
	{
		mHP++;
	}
	if (mHPtimer > 0)
	{
		mHPtimer--;
	}

	UpdatePhysics();
	UpdateFireables();
	UpdatePosition();
	UpdateAnimation();

	mTouch.y = mPosData.y;
	mTouch.x = mPosData.x - 6;

	mAttackZone.y = mPosData.y;
	switch (mDir)
	{
	case LEFT:
		mAttackZone.x = mPosData.x - 20;
		break;
	case RIGHT:
		mAttackZone.x = mPosData.x + 6;
		break;
	default:
		gCons->ConsPrintf("Player has no direction\n");
	}

	mAHM->GetActorAddress(mHatIndex_Sword)->ActorUpdate();

//	gDiagDraw->LogDiagRect(mAttackZone);
//	gDiagDraw->LogDiagRect(mTouch);

//	Node** hat_array = mHats.Dump();
//	for (int i = 0; i < mHats.Size(); i++)
//	{
//		mAHM->GetActorAddress(hat_array[i]->GetItem())->ActorUpdate();
//	}

//	gCons->ConsPrintf("pos : x=%i, y=%i, h=%i, w=%i\n", mPosData.x, mPosData.y, mPosData.h, mPosData.w);
//	gCons->ConsPrintf("draw: x=%i, y=%i, h=%i, w=%i\n", mDrawPos.x, mDrawPos.y, mDrawPos.h, mDrawPos.w);


//	SDL_Rect draw = mDrawPos;
//	draw.x += mPosData.x;
//	draw.y += mPosData.y;
//	gDiagDraw->LogDiagRect(draw);
//	gDiagDraw->LogDiagRect(mPosData);
	//gDiagDraw->LogDiagRect(mTouch);

	//mColMan.DrawTerrain();
	//gCons->ConsPrintf("player x: %i\n", mPosData.x);
	return true;
}

//Sludge_Seal functions

bool Sludge_Seal::Pursue()
{
	
	if (mColMan.DetectSideCollision(&mDestData) == true)
	{
		//gCons->ConsPrintf("I should jump!\n");
		mYmove = -3;
	}
	else
	{
		mYmove = 0;
	}

	Actor* target = mAHM->GetActorAddress(mTarget);

	if ((target->GetX() - mPosData.x > -5))
	{
		mXmove = 2;
		mDir = LEFT;
	}
	else if ((target->GetX() - mPosData.x < 5))
	{
		mXmove = -2;
		mDir = RIGHT;
	}
	else
	{
		mXmove = 0;
		mState = IDLE;

		return true;
	}
	return false;
}

bool Sludge_Seal::rest(int t)
{
	if (mRestTimer >= t)
	{
		mRestTimer = 0;
		return false;
	}
	else
	{
		mRestTimer++;
		return true;
	}
}

bool Sludge_Seal::Wander()
{
	if ((gTime->GetCurrentCycle() - mWanderTimer) >= mWanderLimit)
	{
		mWanderLimit = gRandom->RandRange(20, 30);
		mWanderTimer = gTime->GetCurrentCycle();

		switch (EvenOutcomes(2))
		{
		case 1:
			mDir = LEFT;
			break;
		case 2:
			mDir = RIGHT;
			break;
		}

		mState = IDLE;
		return false;
	}
	else
	{
		if (mColMan.DetectSideCollision(&mDestData) == true)
		{
			//gCons->ConsPrintf("I should jump!\n");
			mYmove = -3;
		}
		else
		{
			mYmove = 0;
		}
		switch (mDir)
		{
		case LEFT:
			mXmove = -1;
			break;
		case RIGHT:
			mXmove = 1;
			break;
		default:
			gCons->ConsPrintf("Wandering In Invalid Direction!\n");
			break;
		}
	}
	return true;
}

bool Sludge_Seal::EventProcess(Event eve)
{	
	if (mState == DEAD)
	{
		return false;
	}
	int AttackerX;

	switch (*eve.GetEventType())
	{
	case ACTOR_COLLISION:
		if (mState == STUN) { break; }
		if (eve.GetEventData()->i == mTarget)
		{
			if (mState == PURSUE)
			{
				//mAHM->GetActorAddress(mTarget)->EventProcess(Event(PLAYER_CHECK, EventData(), mHandle));
				mAHM->GetActorAddress(mTarget)->EventProcess(Event(DAMAGE, mDamage, mHandle));
				mState = IDLE;
			}
		}
		break;
	case SENSOR_COLLISION:
		if (mState == STUN) { break; }
		switch (eve.GetEventData()->sr.st)
		{
		case LOS:
			mAHM->GetActorAddress(eve.GetEventData()->sr.id)->EventProcess(Event(PLAYER_CHECK, *eve.GetEventData(), mHandle));
			
			break;
		default:
			gCons->ConsPrintf("Pursuer Receive invalid sensor response, Unrecognized sensor type\n");
			break;
		}
		break;
	case ANIM_COMPLETE:
		mState = IDLE;
		break;
	case PLAYER_CONFIRM:
		//mAHM->GetActorAddress(eve.GetReturnAddress())->EventProcess(Event(DAMAGE, mDamage, mHandle));

		mTarget = eve.GetEventData()->sr.id;

		if ((rest(50) == false) && (abs(mAHM->GetActorAddress(mTarget)->GetX() - mPosData.x)) >= 14)
		{
			mState = PURSUE;
		}

		break;
	case DAMAGE:
		if (mState == STUN) { break; }

		mHP -= eve.GetEventData()->damd.damage;
		mDamagedTimer = gTime->GetCurrentMS();
		mSoundLib->EventProcess(Event(CREATE_POINT_SOUND, NULL, "sludge_hit", mPosData.x + mDrawPos.x + 5, mPosData.y + 12)); // Should this use mSoundChannel?

		AttackerX = mAHM->GetActorAddress(eve.GetEventData()->damd.attackerID)->GetX();
		if ((AttackerX+6) < (mPosData.x + 11)) //attacker is to the left
		{
			mXspd = 4;
			mYspd = -3;
		}
		else if ((AttackerX+6) > (mPosData.x + 11)) //attacker is to the right
		{
			mXspd = -4;
			mYspd = -3;
		}

		mState = STUN;

		if (mHP <= 0)
		{
			mState = DEAD;
		}
		break;
	default:
		return false;
		//gCons->ConsPrintf("Sludge Seal asked to process unrecognized event\n");
	}

	return false;
}

bool Sludge_Seal::UpdateAnimation()
{
	switch (mState)
	{
	case PURSUE:
		mAnimID = RUN;
		if (mColMan.DetectSwim() == true)
		{
			mAnimID = SWIM;
			break;
		}
		break;
	case DEAD:
		mAnimID = DEAD;
		break;
	case STUN:
	case IDLE:
	default:
		mAnimID = IDLE;
		
		if (mColMan.DetectSwim() == true)
		{
			mAnimID = TREAD;
			break;
		}
	}

	mFrame = mAnimGraph->UpdateAnimation();
	CalcDrawRect();
	return true;
}

bool Sludge_Seal::ActorUpdate()
{
	switch (mState)
	{
	case STUN:
		//gCons->ConsPrintf("seal stunned!\n");
		mXmove = 0;
		if (gTime->GetCurrentMS() - mDamagedTimer >= 700)
		{
			mState = IDLE;
			//gCons->ConsPrintf("seal recovers!\n");
		}
		break;
	case IDLE:
		//rest(20);
		mXmove = 0;
		mYmove = 0;
		//Wander();
		mSpat->EventProcess(Event(CHECK_RECT_SENSOR, LOS, &mLOS, mHandle));
		//mFrame = mAnimPack.ActivateAnimation(IDLE)->GetCurrentFrame();
		break;
	case PURSUE:
		Pursue();
		//mFrame = mAnimPack.ActivateAnimation(RUN)->GetCurrentFrame();
		break;
	case DEAD:
		break;
	default:
		gCons->ConsPrintf("Actor in invalid state\n");
		return false;
	}

	UpdatePhysics();
	
	if ((mPhysMan.Floating() == true) | (mYspd == 0))
	{
		mXspd = 0;
	}

	if (mState != DEAD)
	{
		if (UpdatePosition() == true)
		{
			
			mLOS.y = mPosData.y;
			mLOS.x = mPosData.x;
			mLOS.x -= ((170 - mPosData.w) / 2);
			mLOS.w = 170;
			//gCons->ConsPrintf("Seal: Cell %i\n", mSpatCell);
		}
	}
	UpdateAnimation();
	return true;
}

//

//Loyal_Bug Functions
bool Loyal_Bug::EventProcess(Event eve)
{
	return true;
}

bool Loyal_Bug::UpdateAnimation()
{
	return true;
}

bool Loyal_Bug::ActorUpdate()
{
	if (mMounted) //this check may be unnessecary. Loyal bug may only be able to enter these states when he receives events from a rider anyway. (only riders need to track this at all?)
	{
		switch (mState)
		{
		case RUN_RIGHT:
			mXmove = 6;
			break;
		case WALK_RIGHT:
			mXmove = 3;
			break;
		case RUN_LEFT:
			mXmove = -6;
			break;
		case WALK_LEFT:
			mXmove = -3;
			break;
		case IDLE:
			mXmove = 0;
			mYmove = 0;
			break;
		default:
			gCons->ConsPrintf("Loyal Bug in invalid state\n");
			return false;
		}
	}
	else //Unmounted
	{
		switch (mState)
		{
		case IDLE:
		default:
			gCons->ConsPrintf("Loyal Bug in invalid state\n");
			return false;
		}
	}

	UpdatePhysics();
	UpdateFireables();
	UpdatePosition();
	UpdateAnimation();
	//gCons->ConsPrintf("Loyal Bug x: %i\n", mPosData.x);
	return true;
}

//Wanderer Functions
bool Wanderer::Wander()
{
	if ((gTime->GetCurrentCycle() - mWanderTimer) >= mWanderLimit)
	{
		mWanderLimit = gRandom->RandRange(20, 1000);
		mWanderTimer = gTime->GetCurrentCycle();

		switch (EvenOutcomes(2))
		{
		case 1:
			mDir = LEFT;
			break;
		case 2:
			mDir = RIGHT;
			break;
		}

		mState = IDLE;
		return false;
	}
	else
	{
		if (mColMan.DetectSideCollision(&mDestData) == true)
		{
			//gCons->ConsPrintf("I should jump!\n");
			mYmove = -3;
		}
		else
		{
			mYmove = 0;
		}
		switch (mDir)
		{
		case LEFT:
			mXmove = -1;
			break;
		case RIGHT:
			mXmove = 1;
			break;
		default:
			gCons->ConsPrintf("Wandering In Invalid Direction!\n");
			break;
		}
	}
	return true;
}

bool Wanderer::WaitRandom()
{
	if ((gTime->GetCurrentCycle() - mWaitTimer) >= mWaitLimit)
	{
		mWaitLimit = gRandom->RandRange(30, 750);
		mWaitTimer = gTime->GetCurrentCycle();

		mState = WANDER;
		return false;
	}
	return true;
}

bool Wanderer::EventProcess(Event eve)
{
	switch (*eve.GetEventType())
	{
	case ACTOR_COLLISION:
		break;
	case SENSOR_COLLISION:
		break;
	case DAMAGE:
		break;
	case ANIM_COMPLETE:
		mState = IDLE;
		break;
	default:
		gCons->ConsPrintf("Wanderer asked to process unrecognized event\n");
	}

	return false;
}

bool Wanderer::UpdateAnimation()
{
	switch (mState)
	{
	case WANDER:
		mAnimID = RUN;
		break;
	case IDLE:
	default:
		mAnimID = IDLE;
	}

	mFrame = mAnimGraph->UpdateAnimation();
	return true;
}

bool Wanderer::ActorUpdate()
{
	switch (mState)
	{
	case IDLE:
		mXmove = 0;
		mYmove = 0;
		WaitRandom();
		//mFrame = mAnimPack.ActivateAnimation(IDLE)->GetCurrentFrame();
		break;
	case WANDER:
		Wander();
		break;
	default:
		gCons->ConsPrintf("Actor in invalid state\n");
		return false;
	}
	UpdatePhysics();
	UpdateFireables();
	UpdatePosition();
	UpdateAnimation();
	return true;
}

//Pursuer Functions
bool Pursuer::Pursue()
{
	if (mColMan.DetectSideCollision(&mDestData) == true)
	{
		//gCons->ConsPrintf("I should jump!\n");
		mYmove = -3;
	}
	else
	{
		mYmove = 0;
	}
	
	if ((mTarget->GetX() - mPosData.x > 12))
	{
		mXmove = 2;
		mDir = RIGHT;
	}
	else if ((mTarget->GetX() - mPosData.x < -12))
	{
		mXmove = -2;
		mDir = LEFT;
	}
	else
	{
		mXmove = 0;
		mState = IDLE;
		return true;
	}
	return false;
}

bool Pursuer::rest(int t)
{
	if (mRestTimer >= t)
	{
		mRestTimer = 0;
		return false;
	}
	else
	{
		mRestTimer++;
		return true;
	}
}

bool Pursuer::EventProcess(Event eve)
{
	EventReceiver* DamTar = NULL;
	switch (*eve.GetEventType())
	{
	case ACTOR_COLLISION:
		if (eve.GetEventData()->p == mTarget)
		{
			if (mState == PURSUE)
			{
				mState = IDLE;
			}
		}

		DamTar = (EventReceiver*)eve.GetEventData()->p;
		DamTar->EventProcess(Event(DAMAGE, 10, mHandle));
		break;
	case SENSOR_COLLISION:
		switch (eve.GetEventData()->sr.st)
		{
		case LOS:
			mTarget = (Actor*)eve.GetEventData()->p;

			if ((rest(50) == false) && (abs(mTarget->GetX() - mPosData.x)) >= 14)
			{
				mState = PURSUE;
			}
			break;
		default:
			gCons->ConsPrintf("Pursuer Receive invalid sensor response, Unrecognized sensor type\n");
			break;
		}
		break;
	case ANIM_COMPLETE:
		mState = IDLE;
		break;
	default:
		gCons->ConsPrintf("Pursuer asked to process unrecognized event\n");
	}

	return false;
}

bool Pursuer::UpdateAnimation()
{
	switch (mState)
	{
	case PURSUE:
		mAnimID = RUN;
		break;
	case IDLE:
	default:
		mAnimID = IDLE;
	}

	mFrame = mAnimGraph->UpdateAnimation();
	return true;
}

bool Pursuer::ActorUpdate()
{
	switch (mState)
	{
	case IDLE:
		//rest(20);
		mXmove = 0;
		mYmove = 0;
		mSpat->EventProcess( Event(CHECK_RECT_SENSOR, LOS, &mLOS, mHandle) );
		//mFrame = mAnimPack.ActivateAnimation(IDLE)->GetCurrentFrame();
		break;
	case PURSUE:
		Pursue();
		//mFrame = mAnimPack.ActivateAnimation(RUN)->GetCurrentFrame();
		break;
	default:
		gCons->ConsPrintf("Actor in invalid state\n");
		return false;
	}
	UpdatePhysics();
	UpdateFireables();
	if (UpdatePosition() == true)
	{
		mLOS.y = mPosData.y;
		mLOS.x = mPosData.x;
		mLOS.x -= ( (170 - mPosData.w) / 2 );
		mLOS.w = 170;
	}
	UpdateAnimation();
	return true;
}

//Rabbit
bool Rabbit::Hop()
{
	return false;
}

bool Rabbit::Wander()
{
	if ((gTime->GetCurrentCycle() - mWanderTimer) >= mWanderLimit)
	{
		mWanderLimit = gRandom->RandRange(100, 1000);
		mWanderTimer = gTime->GetCurrentCycle();

		switch (EvenOutcomes(2))
		{
		case 1:
			mDir = LEFT;
			break;
		case 2:
			mDir = RIGHT;
			break;
		}

		mState = IDLE;
		return false;
	}
	else
	{
		if (mColMan.DetectSideCollision(&mDestData) == true)
		{
			//gCons->ConsPrintf("I should jump!\n");
			mYmove = -3;
		}
		else
		{
			mYmove = 0;
		}
		switch (mDir)
		{
		case LEFT:
			mXmove = -1;
			break;
		case RIGHT:
			mXmove = 1;
			break;
		default:
			gCons->ConsPrintf("Wandering In Invalid Direction!\n");
			break;
		}
	}
	return true;
}

bool Rabbit::WaitRandom()
{
	if ((gTime->GetCurrentCycle() - mWaitTimer) >= mWaitLimit)
	{
		mWaitLimit = gRandom->RandRange(30, 1000);
		mWaitTimer = gTime->GetCurrentCycle();

		mState = WANDER;
		return false;
	}
	return true;
}

bool Rabbit::EventProcess(Event eve)
{
	switch (*eve.GetEventType())
	{
	case ACTOR_COLLISION:
		break;
	case SENSOR_COLLISION:
		break;
	case DAMAGE:
		break;
	case ANIM_COMPLETE:
		mState = IDLE;
		break;
	default:
		gCons->ConsPrintf("Wanderer asked to process unrecognized event\n");
	}

	return false;
}

bool Rabbit::UpdateAnimation()
{
	switch (mState)
	{
	case WANDER:
		mAnimID = RUN;
		break;
	case IDLE:
		mAnimID = SLEEP;
		break;
	default:
		mAnimID = IDLE;
	}

	mFrame = mAnimGraph->UpdateAnimation();
	return true;
}

bool Rabbit::ActorUpdate()
{
	switch (mState)
	{
	case IDLE:
		mXmove = 0;
		mYmove = 0;
		WaitRandom();
		//mFrame = mAnimPack.ActivateAnimation(IDLE)->GetCurrentFrame();
		break;
	case WANDER:
		Wander();
		break;
	default:
		gCons->ConsPrintf("Actor in invalid state\n");
		return false;
	}
	UpdatePhysics();
	UpdatePosition();
	UpdateAnimation();
	//gDiagDraw->LogDiagRect(mPosData);
	return true;
}
//