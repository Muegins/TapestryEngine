#ifndef CAMERA_H
#define CAMERA_H

#include "Utils.h"
#include "Console.h"
#include "Actor.h"
#include "Event.h"

class Camera : public EventReceiver
{
public:
	Camera() : mView() {}

	Camera(int H, int W, int X, int Y, int lvlH, int lvlW);

	bool LogBlocker(SDL_Rect* blocker);

	SDL_Rect SmartAdjust(SDL_Rect* blocker);

	SDL_Rect SetCameraPos(SDL_Renderer* ren, int Xpos, int Ypos);

	SDL_Rect SetCameraPosUnbounded(SDL_Renderer* ren, int Xpos, int Ypos);

	bool ArrowKeyMove(SDL_Renderer* ren, int xspd, int yspd, SDL_Event* eve);

	bool ActorFollow(SDL_Renderer* ren, int Xbound, int Ybound);

	bool EventProcess(Event eve);

	int GetCamX()
	{
		return mView.x;
	}

	int GetCamY()
	{
		return mView.y;
	}

	int GetCenterX()
	{
		return mView.x + (mView.w / 2);
	}

	int GetCenterY()
	{
		return mView.y + (mView.h / 2);
	}

	SDL_Rect* GetCamView()
	{
		return &mView;
	}

	void CamResize(int H, int W)
	{
		mView.h = H;
		mView.w = W;
	}

	void SetFollowTarget(Actor* tar)
	{
		mFollowTarget = tar;
	}

protected:
	SDL_Rect mView;
	int mLastMoveUpdate;

	int mlvlH;
	int mlvlW;

	std::vector<SDL_Rect*> mBlockers;

	Actor* mFollowTarget;
};


#endif