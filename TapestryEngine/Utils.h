#ifndef UTILS_H
#define UTILS_H

//#define RELEASE
#define DEBUG


#include <vector>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdarg.h>
#include <stdlib.h>
#include <math.h>
#include <sys/types.h>
#include<sys/stat.h>
//#include <glm/vec4.hpp>
//#include <glm/mat4x4.hpp>

#include "cjson/cJSON.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_mixer.h"
#include "BinaryTree.h"

//Terrain Defines
#define AIR			0x00
#define GROUND		0x01
#define PLATFORM	0x02
#define WATER		0x03
//

//Screen size defines //These must be a whole multiple of the camera size otherwise pixel stretching occurs
#define SCREEN_W 1344
#define SCREEN_H 756
//

//Direction Defines. Used by actor and terrain systems
#define DOWN  3
#define UP	  2
#define LEFT  1 // must be 1 because of SDL draw function
#define RIGHT 0 // must be 0 because of SDL draw function
//

//Time Defines
//#define MS_PER_FRAME 16 //60fps this is normal speed
//#define MS_PER_FRAME 32 //30fps
#define MS_PER_FRAME 48 //20fps keeps kolbo from huffing and puffing
#define FRAMES_PER_SECOND (1/MS_PER_FRAME)*1000 //62.5 @16ms

#define CLOCKS_PER_FRAME (CLOCKS_PER_SEC/FRAMES_PER_SECOND)
//


//Actor State Defines
#define IDLE				10
#define IDLE_DRAWN			11
#define STUN				12
#define FALL				20
#define FALL_DRAWN			21
#define JUMP_TO_FALL		30
#define JUMP_TO_FALL_DRAWN	31
#define RUN					40
#define RUN_DRAWN			41
#define IDLE_BEGIN			50
#define IDLE_BEGIN_DRAWN	51
#define JUMP				60
#define JUMP_DRAWN			61
#define WANDER				70
#define PURSUE				80
#define SWIM				110
#define SWIM_BEGIN			111
#define TREAD				120
#define LOOK				121
#define EAT					122
#define SLEEP				123
#define PARTICLE			124
#define ATTACK				130
#define ALIVE				140
#define DEAD				150
#define DIE					151

#define SWIM_LEFT			160
#define SWIM_RIGHT			161
#define SWIM_DOWN			162
#define SWIM_UP				163

#define RUN_LEFT			0x1
#define RUN_RIGHT			0x02
#define RUN_DOWN			0x003
#define RUN_UP				0x0004

#define WALK_LEFT			0x5
#define WALK_RIGHT			0x06
#define WALK_DOWN			0x007
#define WALK_UP				0x0008

#define GATE_UP				201
#define GATE_DOWN			202
#define GATE_LOWER			203
#define GATE_LOWER_BEGIN	204
#define GATE_RAISE			205

#define SPLASH	   90
#define HAZE	   100

#define FADE_BLACK 210
#define FADE_RED   211
//

//This is a strange place for this stuff. Should maybe be its own ParticleTypeData.h
struct drift_data 
{
	int mXspd;
	int mYspd;
};

union ParticleTypeData
{
	bool NoData;
	drift_data drift;
};

ParticleTypeData NullPTdata();
//

//struct ActHandle
//{
//	int id;
//};

typedef int ActHandle;

class Time
{
public:

	Time() : mCycle(0) {};

	int ProgressCycle()
	{
		mCycle = (mCycle + 1);
		return mCycle;
	}

	int GetCurrentCycle()
	{
		return mCycle;
	}

	int GetCurrentMS()
	{
		return (mCycle*MS_PER_FRAME);
	}
protected:

	int mCycle;
};

class Random
{
public:
	Random();

	int RandRange(int min, int max);
protected:

	int mSeed;
};

int GetRealTimeMS();

SDL_Surface* LoadSurfaceBMP(const char* filename);

TTF_Font* LoadFont(const char* file, int ptsize);

cJSON * LoadJSON(const char* filename);

void PrintJSON(cJSON* json);

float GetSign(float x);

bool DetectRectIntersect(SDL_Rect* r1, SDL_Rect* r2);

bool DetectCenterPointIntersect(SDL_Rect* zone, SDL_Rect* point); //Detects if the center of rectangle "point" is within rectangle "zone"

int CalcDistance(int x1, int y1, int x2, int y2);

int EvenOutcomes(int NumberofOutcomes);

bool IsEven(int i);

extern Time* gTime;
extern Random* gRandom;

#endif
