#ifndef SOUND_H
#define SOUND_H

#include "Utils.h"
#include "Console.h"
#include "Event.h"

#define MAX_VOL_RANGE 300.0
#define MIN_VOL_RANGE 1500.0
#define FADE_DISTANCE (MIN_VOL_RANGE - MAX_VOL_RANGE)

Mix_Music* LoadMusic(char* filename);
Mix_Chunk* LoadSound(char* filename);

class ChannelManager
{
public:

	ChannelManager() {}

	int AssignChannel()
	{
		for (int i = 0; i < (int)mChannels.size(); i++)
		{
			if ( (mChannels.at(i) = false) && (Mix_Playing(i) == false))
			{
				return i;
			}
		}
		mChannels.push_back(true);
		Mix_AllocateChannels(mChannels.size());
		return (mChannels.size() - 1);
	}

	void FreeChannel(int channel)
	{
		mChannels.at(channel) = false;
	}

	bool PlaySound(int channel, Mix_Chunk* snd, int distance = -1); //outdated

	bool PlayLoop(int channel, Mix_Chunk* snd, int distance = -1); //outdated

protected:

	std::vector<bool> mChannels;
};

class PointSound //A sound that plays at a point and attenuates with distance
{
public:

	PointSound(int x, int y, Mix_Chunk* sound, int id) : mX(x), mY(y), mSound(sound), mID(id), mSpawnDate(gTime->GetCurrentCycle())
	{
		//mFeed.EventProcess(Event(SPAWN, (void*)&mSoundChannel));
	}

	~PointSound()
	{
		//mFeed.EventProcess(Event(SOUND_COMPLETE, (void*)this));
	}

	int setID(int id)
	{
		return mID = id;
	}

	int GetID()
	{
		return mID;
	}

	Mix_Chunk* GetChunk()
	{
		return mSound;
	}

	void SetChannel(int chan)
	{
		mSoundChannel = chan;
	}

	int GetChannel()
	{
		return mSoundChannel;
	}

	int GetX()
	{
		return mX;
	}

	int GetY()
	{
		return mY;
	}

	int GetSpawnDate()
	{
		return mSpawnDate;
	}

	bool PlayPointSound(int listen_x, int listen_y)
	{
		if (Mix_Playing(mSoundChannel) == false)
		{
			int dist = CalcDistance(mX, mY, listen_x, listen_y);

			if (dist >= MIN_VOL_RANGE) //If the sound is out of hearing range
			{
				//gCons->ConsPrintf("Sound out of range\n\n");
				return false;
			}
			else
			{
				Mix_PlayChannel(mSoundChannel, mSound, 0);
				if (dist <= MAX_VOL_RANGE) //if the sound is within range to play for no attenuation
				{
					//gCons->ConsPrintf("Sound within maximum volume range\n\n");
					Mix_SetDistance(mSoundChannel, 0);
				}
				else //between min and max volume ranges
				{
					int fade = int(((float)(dist - MAX_VOL_RANGE) / FADE_DISTANCE) * 255.0);

					//gCons->ConsPrintf("Attenuation value: %i\n\n", fade);
					Mix_SetDistance(mSoundChannel, fade);
				}
			}

			return true;
		}
		else
		{
			mFeed.EventProcess(Event(SOUND_COMPLETE, this)); //not sure this should be called here
		}
		return false;
	}

	void FadeOut(int fade_time)
	{
		Mix_FadeOutChannel(mSoundChannel, fade_time);
	}

	EventFeed mFeed;

protected:

	int mX;
	int mY;
	Mix_Chunk* mSound;

	int mSoundChannel;

	int mID;

	int mSpawnDate;
};

class RegionSound //Sounds that can be heard in a retangular region
{
public:

	RegionSound(SDL_Rect region, int id) : mRegion(region), mID(id)
	{
		//mFeed.EventProcess(Event(SPAWN, (void*)&mSoundChannel));
	}

	~RegionSound()
	{
		//mFeed.EventProcess(Event(SOUND_COMPLETE, (void*)this));
	}

	int setID(int id)
	{
		return mID = id;
	}

	int GetID()
	{
		return mID;
	}

	void SetChannel(int chan)
	{
		mSoundChannel = chan;
	}

	int GetChannel()
	{
		return mSoundChannel;
	}

	bool LogTrack(Mix_Chunk* snd)
	{
		mLoops.push_back(snd);
		return true;
	}

	bool PlayRegionSound(SDL_Rect* pos)
	{
		if (DetectCenterPointIntersect(&mRegion, pos) == false)
		{
			Mix_FadeOutChannel(mSoundChannel, 5000);
		}
		else
		{
			if (Mix_Playing(mSoundChannel) == false)
			{
				for (int i = 0; i < (int)mLoops.size(); i++)
				{
					Mix_FadeInChannel(mSoundChannel, mLoops.at(i), -1, 5000);
				}
				return true;
			}
		}
		return false;
	}

	EventFeed mFeed;

protected:

	SDL_Rect mRegion;

	std::vector<Mix_Chunk*> mLoops;
	
	int mSoundChannel;

	int mID;
};

class SoundManager : public EventReceiver //needs to have functions moved to cpp
{
public:

	SoundManager() 
	{
		mChannelManager = ChannelManager();
		mMusic_Channel = mChannelManager.AssignChannel();
	}

	~SoundManager()
	{
		mChannelManager.FreeChannel(mMusic_Channel);
	}

	bool LogSoundData(Mix_Chunk* snd, char* name)
	{
		mSoundData.push_back(snd);
		mNames.push_back(name);
		return true;
	}

	Mix_Chunk* GetSoundData(char* name)
	{
		for (int i = 0; i < (int)mNames.size(); i++)
		{
			if (!strcmp(name, mNames.at(i)))
			{
				return mSoundData.at(i);
			}
		}
		return NULL;
	}
	
	

	PointSound* SpawnPointSound(int x, int y, char* name)
	{
		PointSound* ps = new PointSound(x,y,GetSoundData(name), (int)(mEffects.size()) );
		ps->SetChannel(mChannelManager.AssignChannel());
		ps->mFeed.Subscribe(this);
		mEffects.push_back(ps);

		FadeDuplicates(ps->GetChunk(), 0);

		return ps;
	}

	RegionSound* SpawnRegionSound(SDL_Rect region)
	{
		RegionSound* rs = new RegionSound(region, (int)(mRegions.size()));
		rs->SetChannel(mChannelManager.AssignChannel());
		rs->mFeed.Subscribe(this);
		mRegions.push_back(rs);

		return rs;
	}

	bool ClearPointSound(PointSound* ps)
	{
		mChannelManager.FreeChannel(ps->GetChannel());
		
		mEffects.erase(mEffects.begin() + ps->GetID());

		for (int i = 0; i < (int)(mEffects.size()); i++)
		{
			mEffects.at(i)->setID(i);
		}

		return false;
	}

	std::vector<PointSound*>* GetPointSounds()
	{
		return &mEffects;
	}

	ChannelManager* GetChannelManager()
	{
		return &mChannelManager;
	}

	bool FadeDuplicates(Mix_Chunk* snd, int max_dupes) //This function does the job but its really expensive, Would work better with improved memory management
	{
		std::vector<int> dupes;
		for (int i = 0; i < (int)mEffects.size(); i++)
		{
			if (snd == mEffects.at(i)->GetChunk())
			{
				dupes.push_back(i);
			}
		}

		for (int k = (int)dupes.size(); k > max_dupes;)
		{
			int oldest_index = -1;
			int oldest = gTime->GetCurrentCycle();
			for (int j = 0; j < (int)dupes.size(); j++)
			{
				if (mEffects.at(dupes.at(j))->GetSpawnDate() <= oldest) //if mEffects[j] is older than mEffects[j - 1]
				{
					oldest = mEffects.at(dupes.at(j))->GetSpawnDate();
					oldest_index = j;
				}
			}
			if (oldest_index == -1)
			{
				return false;
			}
			mEffects.at(dupes.at(oldest_index))->FadeOut(1);
			//gCons->ConsPrintf("Sound Faded\n");
			dupes.erase(dupes.begin() + oldest_index);
			k = (int)dupes.size();
		}
		return true;
	}

	bool UpdatePointSounds(int listen_x, int listen_y);

	bool UpdateRegionSounds(SDL_Rect* pos);

	bool EventProcess(Event eve);
	
protected:

	ChannelManager mChannelManager;

	std::vector<Mix_Chunk*> mSoundData;
	std::vector<char*> mNames;

	std::vector<PointSound*> mEffects;
	std::vector<RegionSound*> mRegions;

	int mMusic_Channel;

};

#endif
