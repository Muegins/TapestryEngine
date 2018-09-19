#include "Physics.h"

//Spring
Spring::Spring(int* pos, float* vel, float k,  int n, float damp, int Vmax, int Amax, int ExMax)
{
	mPos = pos;
	mVelocity = vel;
	mSpringK = k;
	mDamper = damp;
	mNeutral = n;
	
	mMaxExten = ExMax;
	mMaxVel = Vmax;
	mMaxAccel = Amax;
}

int Spring::ZeroNeutralAxis()
{
	mNeutral = *mPos;
	return mNeutral;
}

float Spring::CalcAccel()
{
	float disp = (float)((mNeutral - *mPos));

	if (mMaxExten != 0)
	{
		if (fabs(disp) > mMaxExten)
		{
			disp = (float)mMaxExten*GetSign(disp);
		}
	}

	float Accel = (disp)*mSpringK;
	if (mMaxAccel != 0)
	{
		if (fabs(Accel) > mMaxAccel)
		{
			//gCons->ConsPrintf("Bouyant Accel = %f\n", mMaxAccel*GetSign(Accel));
			return mMaxAccel*GetSign(Accel);
		}
	}
	//gCons->ConsPrintf("Bouyant Accel = %f\n", Accel);
	return Accel;
}

bool Spring::CalcVelocity()
{
	if (mMaxVel != 0)
	{
		if ( abs( (int)(*mVelocity + CalcAccel()) ) > mMaxVel)
		{
			*mVelocity = mMaxVel*GetSign(*mVelocity);
			return true;
		}
	}
	//*mVelocity += CalcAccel();
	*mVelocity = (*mVelocity + CalcAccel())*mDamper;
	//gCons->ConsPrintf("Spring Vel = %f\n", *mVelocity);
	return true;
}

//Physics
PhysicsManager::PhysicsManager(float GravAccel, float BouyancyK, int* pos, float* Xvel, float* Yvel, bool Grav )
{
	mGravAccel = GravAccel;
	mGravity = Grav;
	mFloating = false;
	mXvel = Xvel;
	mYvel = Yvel;
	mBouyancy = Spring(pos, Yvel, BouyancyK, 0, (float)0.85, 9, 0, 10);
}