#ifndef PHYSICS_H
#define PHYSICS_H

#include "Utils.h"
#include "Console.h"

class Spring
{
public:

	Spring() : mSpringK(0), mNeutral(0) {}

	Spring(int* pos, float* vel, float k,  int n, float damp = 1, int Vmax = 0, int Amax = 0, int ExMax = 0);

	int ZeroNeutralAxis();

	float CalcAccel();

	bool CalcVelocity();

protected:
	
	int* mPos;
	float* mVelocity;
	int mMaxVel;
	int mMaxAccel;
	int mMaxExten;
	float mSpringK;
	float mDamper;
	int   mNeutral;
};

class PhysicsManager
{
public:

	PhysicsManager() : mGravAccel(0) {}

	PhysicsManager(float GravAccel, float BouyancyK, int* pos, float* Xvel, float* Yvel, bool Grav = true);

	int ZeroBouyantSurface()
	{
		return mBouyancy.ZeroNeutralAxis();
	}

	bool SetFloating(bool state)
	{
		return mFloating = state;
	}

	bool Floating()
	{
		return mFloating;
	}

	bool SetGravity(bool state)
	{
		return mGravity = state;
	}

	bool Gravity()
	{
		return mGravity;
	}

	Spring* GetBouyancy()
	{
		return &mBouyancy;
	}

	bool ApplyGravity()
	{
		if (mGravity == true)
		{
			*mYvel += mGravAccel;
			//gCons->ConsPrintf("Gravity Applied!\n");
			return true;
		}
		else
		{
			return false;
		}
	}

	bool ApplyBouyancy()
	{
		if (mFloating == true)
		{
			mBouyancy.CalcVelocity();
			return true;
		}
		else
		{
			return false;
		}
	}

	bool ApplyPhysics()
	{
		ApplyGravity();
		ApplyBouyancy();
		
		return true;
	}

protected:

	float* mYvel;
	float* mXvel;
	bool mGravity;
	float mGravAccel;
	bool mFloating;
	Spring mBouyancy;

};

#endif

