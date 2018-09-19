#ifndef EMITTER_H
#define EMITTER_H

#include "Console.h"
#include "Utils.h"
#include "Actor.h"

class Emitter
{
public:

	Emitter(int x, int y, EventReceiver* ParticleManager, char* name, int count, ParticleTypeData data) : mX(x), mY(y), mPrtMan(ParticleManager), mPrtName(name), mPrtCount(count), mData(data)
	{
	}

	char* GetType()
	{
		return mPrtType;
	}

	char* GetName()
	{
		return mPrtName;
	}

	int GetX()
	{
		return mX;
	}

	int GetY()
	{
		return mY;
	}

	ParticleTypeData GetData()
	{
		return mData;
	}

	bool EmitParticle();

protected:

	int mX;
	int mY;
	EventReceiver* mPrtMan;

	char* mPrtType;
	char* mPrtName;
	int mPrtCount;

	int mDir;
	int mSpd;

	ParticleTypeData mData; //union to store data for different types of particles

	Actor* Particles;
};

#endif
