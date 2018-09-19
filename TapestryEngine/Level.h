#ifndef LEVEL_H
#define LEVEL_H

#include "Utils.h"
#include "Console.h"
#include "Context.h"

#include "Actor.h"
#include "ActorCollision.h"
#include "Particle.h"
#include "Camera.h"
#include "Event.h"
#include "Input.h"
#include "symbol.h"
#include "MiscDraw.h"
#include "sound.h"
#include "HUD.h"
#include "Dialogue.h"

struct ActorName
{
	char* name;
	Actor* act;
};

Actor* FindRef(std::vector<ActorName*> refs, char* name);

class Level : public Context, public EventReceiver
{
public:

	Level() {}

	Level(SDL_Renderer* ren, Control* ctrl)
	{
		mRen = ren;
		mInput = ctrl;
	}

	bool LoadWorld(cJSON* level);

	bool LoadCamera(cJSON* level);

	bool LoadAnimations(cJSON* level);

	bool LoadAnimGraph(cJSON* anim_pack);

	bool LoadActors(cJSON* level);

	bool LoadParticles(cJSON* level);

	bool LoadSounds(cJSON* level);

	bool LoadHud(cJSON* level);

	bool Load(const char* filename);

	bool Update();

	bool EventProcess(Event eve);
	
	ActorHandleManager mAHM;
	SpatialMonitor mSpatMon;
	Control* mInput;
	ParticleManager mPrtLib;
	SoundManager mSoundLib;
	

	int mHeight;
	int mWidth;
	Camera mCam;

	SDL_Surface* mColMap;

	std::vector<AnimDataPack*> mAnimData;
	std::vector<AnimGraphData*> mAnimGraphs;

	std::vector<Actor*> mCast; //Used to draw all actors, maybe should use AHM instead

	std::vector<SDL_Texture*> mBack;
	std::vector<float> mParallax_back;

	std::vector<SDL_Texture*> mFore;

	std::vector<SDL_Texture*> mOver;
	std::vector<float> mParallax_over;

	HUD mHUD;

protected:

	char** mAnim_names;
	Player* mPlayer;

};

#endif
