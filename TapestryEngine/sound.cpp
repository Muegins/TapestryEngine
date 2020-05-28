#include "sound.h"
#include "Actor.h"

Mix_Music* LoadMusic(char* filename)
{
//#ifdef DEBUG
//	const char* basepath = "/home/sebastian/projects/TapestryEngine/TapestryEngine/sounds/";
//#endif

//#ifdef RELEASE
	const char* basepath = "./TapestryEngine/sounds/";
//#endif

	char pathbuffer[1024];
	strcpy(pathbuffer, basepath);

	Mix_Music* sound = Mix_LoadMUS(strcat(pathbuffer, filename));
	if (sound == NULL)
	{
		gCons->ConsPrintf("Mix_Music Error: %s", Mix_GetError());
		return NULL;
	}
	return sound;
}

Mix_Chunk* LoadSound(char* filename)
{
//#ifdef DEBUG
//	const char* basepath = "/home/sebastian/projects/TapestryEngine/TapestryEngine/sounds/";
//#endif

//#ifdef RELEASE
	const char* basepath = "./TapestryEngine/sounds/";
//#endif

	char pathbuffer[1024];
	strcpy(pathbuffer, basepath);

	Mix_Chunk* sound = Mix_LoadWAV(strcat(pathbuffer, filename));
	if (sound == NULL)
	{
		char s[1024];
		strcpy(s, Mix_GetError());
		gCons->ConsPrintf("Mix_Music Error: %s", Mix_GetError());
		return NULL;
	}
	return sound;
}

bool ChannelManager::PlaySound(int channel, Mix_Chunk* snd, int distance)
{
	if (distance = -1)
	{
		Mix_PlayChannel(channel, snd, 0);
		Mix_SetDistance(channel, 0);
		return true;
	}
	
	//gCons->ConsPrintf("Distance from camera: %i\n", distance);
	if (distance >= MIN_VOL_RANGE) //If the sound is out of hearing range
	{
		//gCons->ConsPrintf("Sound out of range\n\n");
		return false;
	}
	else
	{
		Mix_PlayChannel(channel, snd, 0);
		if (distance <= MAX_VOL_RANGE) //if the sound is within range to play for no attenuation
		{
			//gCons->ConsPrintf("Sound within maximum volume range\n\n");
			//Mix_SetDistance(channel, 0);
		}
		else //between min and max volume ranges
		{
			int fade = int(((float)(distance - MAX_VOL_RANGE) / FADE_DISTANCE) * 255.0);

			//gCons->ConsPrintf("Attenuation value: %i\n\n", fade);
			Mix_SetDistance(channel, fade);
		}
	}
	return true;
}

bool ChannelManager::PlayLoop(int channel, Mix_Chunk* snd, int distance)
{
	if (distance = -1)
	{
		Mix_PlayChannel(channel, snd, -1);
		Mix_SetDistance(channel, 0);
		return true;
	}

	//gCons->ConsPrintf("Distance from camera: %i\n", distance);
	if (distance >= MIN_VOL_RANGE) //If the sound is out of hearing range
	{
		//gCons->ConsPrintf("Sound out of range\n\n");
		return false;
	}
	else
	{
		Mix_PlayChannel(channel, snd, -1);
		if (distance <= MAX_VOL_RANGE) //if the sound is within range to play for no attenuation
		{
			//gCons->ConsPrintf("Sound within maximum volume range\n\n");
			//Mix_SetDistance(channel, 0);
		}
		else //between min and max volume ranges
		{
			int fade = int(((float)(distance - MAX_VOL_RANGE) / FADE_DISTANCE) * 255.0);

			//gCons->ConsPrintf("Attenuation value: %i\n\n", fade);
			Mix_SetDistance(channel, fade);
		}
	}
	return true;
}

//Sound Manager Functions
bool SoundManager::UpdatePointSounds(int listen_x, int listen_y)
{
	for (int i = 0; i < (int)mEffects.size(); i++)
	{
		mEffects.at(i)->PlayPointSound(listen_x, listen_y);
	}
	return true;
}

bool SoundManager::UpdateRegionSounds(SDL_Rect* pos)
{
	for (int i = 0; i < (int)mRegions.size(); i++)
	{
		mRegions.at(i)->PlayRegionSound(pos);
	}
	return true;
}

bool SoundManager::EventProcess(Event eve)
{
	switch (*eve.GetEventType())
	{
	case CREATE_POINT_SOUND:
		SpawnPointSound(eve.GetEventData()->psd.x, eve.GetEventData()->psd.y, eve.GetEventData()->psd.name);
		return true;
		break;
	case ACTOR_PLAY_SOUND:
		return true;
		break;
	case SPAWN:
	{
		int* channel = (int*)eve.GetEventData()->p;
		*channel = mChannelManager.AssignChannel();
		return true;
		break;
	}
	case DEATH:
		mChannelManager.FreeChannel(((Actor*)(eve.GetEventData()->p))->GetChannel());
		return true;
		break;
	case SOUND_COMPLETE:
		ClearPointSound((PointSound*)eve.GetEventData()->p);
		return true;
		break;
	default:
		gCons->ConsPrintf("Sound Manager recieved unregcognized even\n");
		return false;
		break;
	}
}
