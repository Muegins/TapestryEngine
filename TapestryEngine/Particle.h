#ifndef PARTICLE_H
#define PARTICLE_H

#include "Utils.h"
#include "Console.h"
#include "Event.h"
#include "Actor.h"

struct ParticleData
{
	//AnimDataPack* AnimData;
	AnimGraph* AnimData;
	int Height;
	int Width;
	EventReceiver* spat;
};


class Particle : public Mobile
{
public:
//	Particle() {}

	Particle(AnimGraph* AnimData, SDL_Rect Pos, int ID, ActorHandleManager* AHM);

//	Particle(const Particle& that)
//	{
//		gCons->ConsPrintf("no pls\n");
//	}

	~Particle()
	{

	}

	//bool EventProcess(Event eve);

	//bool UpdateAnimation();

	//bool ActorUpdate();

	void setID(int i)
	{
		mID = i;
	}

	int GetID()
	{
		return mID;
	}

	EventFeed mFeed;
protected:

	int mID;

private:
	//Particle(const Particle& that);
};

class P_static : public Particle
{
public:

	P_static(AnimGraph* AnimData, SDL_Rect Pos, int ID, ActorHandleManager* AHM) : Particle(AnimData, Pos, ID, AHM)
	{}

	bool EventProcess(Event eve);

	bool UpdateAnimation();

	bool ActorUpdate();

protected:
};


class P_drift : public Particle
{
public:

	P_drift(AnimGraph* AnimData, SDL_Rect Pos, int ID, ActorHandleManager* AHM, drift_data data);

	bool Drift();

	bool EventProcess(Event eve);

	bool UpdateAnimation();

	bool ActorUpdate();

protected:
	
	drift_data mData;

};

class ParticleManager : public EventReceiver
{
public:

	bool LogParticleData(ParticleData* pd, char* name)
	{
		mParticleData.push_back(pd);
		mNames.push_back(name);
		particlesKilled = 0;
		return true;
	}

	ParticleData* GetParticleData(char* name)
	{
		for (int i = 0; i < (int)mParticleData.size(); i++)
		{
			if (!strcmp(name, mNames.at(i)))
			{
				return mParticleData.at(i);
			}
		}
		return NULL;
	}

	bool SpawnParticle(char* type, char* name, int x, int y, ParticleTypeData ptdata = NullPTdata() );

	bool ClearParticle(Particle* prt);

	bool EventProcess(Event eve);
	
	std::vector<Particle*>* GetParticles()
	{
		return &mParticles;
	}

protected:

	std::vector<ParticleData*> mParticleData;
	std::vector<char*> mNames;

	std::vector<Particle*> mParticles;

	int particlesKilled;
};

#endif