#ifndef EVENT_H
#define EVENT_H

#include "Utils.h"
#include "Console.h"

enum EventType
{
	UNSUBSCRIBE,

	//ASSIGN_HANDLE,
	//GET_ACTOR_ADDRESS,

	ANIM_COMPLETE,

	KEY_DOWN,
	KEY_UP,

	ACTOR_COLLISION,
	SENSOR_COLLISION,
	PLAYER_CHECK,
	PLAYER_CONFIRM,

	MOVED_THIS_FRAME,
	CHECK_RECT_SENSOR,
	CHECK_BLOCKERS,

	CAMERA_TARGET,

	EMIT_PARTICLE,
	CREATE_PARTICLE,

	CREATE_POINT_SOUND,
	ACTOR_PLAY_SOUND,
	SOUND_COMPLETE,

	SWITCH,

	DIALOGUE,
	SCROLL,
	TERMINATE_DIALOGUE,

	FADE,

	TELEPORT,

	INTERACT,

	DAMAGE,

	SPAWN,
	DEATH,

	GAME_OVER
};

enum SensorType
{
	LOS, //Line Of Sight
	Attack,
	Touch,
};

struct SensorData
{
	SensorType st;
	SDL_Rect* sensor;
	int id;
};

struct SensorResponse
{
	SensorType st;
	int id;
};

struct PointSpawnData
{
	int x;
	int y;
	const char* name;
	const char* type;
};

struct DialogueData
{
	const char* str;
	int talkerID;
};

struct FadeData
{
	int duration;
	int color;
	int opacity;
};

struct DamageData
{
	int damage;
	int attackerID;
};

union EventData
{
	int i;
	void* p;
	bool b;
	const char* str;
	SDL_Rect* rect;
	SensorData sd;
	SensorResponse sr;
	PointSpawnData psd;
	DialogueData dd;
	FadeData fd;
	DamageData damd;
};

class EventReceiver; //Forward Declare event receiver

class Event
{
public:
	Event() : mType(), mEvData() {} //, mReturnAddress(NULL) {}

	Event(EventType EvType) : mType(EvType), mEvData() {}

	//Event(EventType EvType, ActHandle ReturnAddress = NULL) : mType(EvType), mEvData(), mReturnAddress(ReturnAddress) {}

	Event(EventType EvType, EventData EvData, int ReturnAddress = NULL) : mType(EvType), mEvData(EvData), mReturnAddress(ReturnAddress) {}

	Event(EventType EvType, int i) : mType(EvType), mReturnAddress(NULL)
	{
		mEvData.i = i;
	}

	Event(EventType EvType, void* P) : mType(EvType), mReturnAddress(NULL)
	{
		mEvData.p = P;
	}

	Event(EventType EvType, const char* str) : mType(EvType), mReturnAddress(NULL)
	{
		mEvData.str = str;
	}

	Event(EventType EvType, SensorType SeType, SDL_Rect* sensor, int ID) : mType(EvType), mReturnAddress(NULL) //CHECK_RECT_SENSOR constructor
	{
		mEvData.sd.st = SeType;
		mEvData.sd.sensor = sensor;
		mEvData.sd.id = ID;
	}

	Event(EventType EvType, SensorType SeType, ActHandle ID) : mType(EvType), mReturnAddress(NULL) //collision response constructor: SENSOR_COLLISION,
	{
		mEvData.sr.st = SeType;
		mEvData.sr.id = ID;
	}

	Event(EventType EvType, const char* type, const char* name, int x, int y) : mType(EvType), mReturnAddress(NULL)
	{
		mEvData.psd.x = x;
		mEvData.psd.y = y;
		mEvData.psd.name = name;
		mEvData.psd.type = type;
	}

	Event(EventType EvType, const char* str, int talkID) : mType(EvType), mReturnAddress(NULL)
	{
		mEvData.dd.str = str;
		mEvData.dd.talkerID = talkID;
	}

	Event(EventType EvType, int duration, int color, int opacity) : mType(EvType), mReturnAddress(NULL)
	{
		mEvData.fd.duration = duration;
		mEvData.fd.color = color;
		mEvData.fd.opacity = opacity;
	}

	Event(EventType EvType, int damage, int attacker_handle) : mType(EvType), mReturnAddress(NULL)
	{
		mEvData.damd.damage = damage;
		mEvData.damd.attackerID = attacker_handle;
	}

	EventType* GetEventType()
	{
		return &mType;
	}

	EventData* GetEventData()
	{
		return &mEvData;
	}

	int GetReturnAddress()
	{
		if(mReturnAddress != NULL)
		{
			return mReturnAddress;
		}
		gCons->ConsPrintf("No return address listed for this event\n");
		return NULL;
	}

protected:

	EventType mType;
	EventData mEvData;
	int mReturnAddress;
};

class EventReceiver
{
public:

	virtual bool EventProcess(Event eve) = 0;
};

class EventFeed  :  EventReceiver
{
public:
	
	EventFeed() : mSubs(), mNumberOfSubs(0) {}

	bool Subscribe(EventReceiver* sub);

	bool Unsubscribe(EventReceiver* sub);

	bool EventProcess(Event eve);

protected:

	std::vector<EventReceiver*> mSubs;
	int mNumberOfSubs;
};

class EventManager
{
public:
protected:
};

#endif
