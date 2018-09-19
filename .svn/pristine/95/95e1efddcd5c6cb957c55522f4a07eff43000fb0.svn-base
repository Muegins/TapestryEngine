#include "Camera.h"


Camera::Camera(int H, int W, int X, int Y, int lvlH, int lvlW)
{
	mView.h = H;
	mView.w = W;
	
	mView.x = X;
	mView.y = Y;

	mlvlH = lvlH;
	mlvlW = lvlW;
}

bool Camera::LogBlocker(SDL_Rect* blocker)
{
	mBlockers.push_back(blocker);
	return false;
}

SDL_Rect Camera::SmartAdjust(SDL_Rect* blocker)
{
	if (blocker->h == 1)
	{
		int bisect = (int)((float)mView.h / 2) + mView.y;
		if (blocker->y >= bisect)
		{
			//slide camera up
			mView.y = blocker->y - mView.h;
		}
		else if (blocker->y < bisect)
		{
			//slide camera down
			mView.y = blocker->y;
		}
		else
		{
			//this should never happen
		}
	}
	else if (blocker->w == 1)
	{
		int bisect = (int)((float)mView.w / 2) + mView.x;
		if (blocker->x >= bisect)
		{
			mView.x = blocker->x - mView.w;
		}
		else if (blocker->x < bisect)
		{
			mView.x = blocker->x;
		}
		else
		{
			//this should never happen
		}
	}
	else
	{
		gCons->ConsPrintf("Camera logged invalid blocker neither h nor w == 1\n");
	}
	return mView;
}

SDL_Rect Camera::SetCameraPos(SDL_Renderer* ren, int Xpos, int Ypos)
{
	int wrldX = Xpos;
	int wrldY = Ypos;
	
	if (Xpos < 0)
	{
		wrldX = 0;
	}
	else if ((Xpos + mView.w) > mlvlW)
	{
		wrldX = mlvlW - mView.w;
	}

	if (Ypos < 0)
	{
		wrldY = 0;
	}
	else if ((Ypos + mView.h) > mlvlH)
	{
		wrldY = mlvlH - mView.h;
	}

	mView.x = wrldX;
	mView.y = wrldY;

	for (int i = 0; i < (int)mBlockers.size(); i++)
	{
		if (DetectRectIntersect(&mView, mBlockers.at(i)))
		{
			//gCons->ConsPrintf("Camera is hitting blocker\n");
			SmartAdjust(mBlockers.at(i));
		}
	}
	

	//gCons->ConsPrintf("cam bounds: x= %i - %i, y= %i - %i \n", view.x, (view.x + view.w), view.y, (view.y + view.h));

	return mView;
}

SDL_Rect Camera::SetCameraPosUnbounded(SDL_Renderer* ren, int Xpos, int Ypos)
{
//	wrldX = Xpos;
	//wrldY = Ypos;

	mView.x = Xpos;
	mView.y = Ypos;

	//gCons->ConsPrintf("cam bounds: x= %i - %i, y= %i - %i \n", view.x, (view.x + view.w), view.y, (view.y + view.h));

	return mView;
}

bool Camera::ArrowKeyMove(SDL_Renderer* ren, int xspd, int yspd, SDL_Event* eve)
{
	if (eve->key.type == SDL_KEYUP) return 0;

	switch (eve->key.keysym.sym)
	{
	case  SDLK_DOWN:
		mView.y = mView.y + yspd;
		break;
	case    SDLK_UP:
		mView.y = mView.y + -yspd;
		break;
	case  SDLK_LEFT:
		mView.x = mView.x + -xspd;
		break;
	case SDLK_RIGHT:
		mView.x = mView.x + xspd;
		break;
	}
	SetCameraPos(ren, mView.x, mView.y);
	return 0;
}

bool Camera::ActorFollow(SDL_Renderer* ren, int Xbound, int Ybound)
{
	if (mFollowTarget->GetX() < (mView.x + Xbound))
	{
		mView.x = (mFollowTarget->GetX() - Xbound);
		//gCons->ConsPrintf("LEFT\n");
	}	
	if (mFollowTarget->GetX() + mFollowTarget->GetWidth() > ((mView.x + mView.w) - Xbound))
	{
		mView.x = mFollowTarget->GetX() + mFollowTarget->GetWidth() - mView.w + Xbound;
		//gCons->ConsPrintf("RIGHT\n");
	}

	if (mFollowTarget->GetY() < (mView.y + Ybound))
	{
		mView.y = (mFollowTarget->GetY() - Ybound);
		//gCons->ConsPrintf("LEFT\n");
	}
	if (mFollowTarget->GetY() + mFollowTarget->GetHeight() > ((mView.y + mView.h) - Ybound))
	{
		mView.y = mFollowTarget->GetY() + mFollowTarget->GetHeight() - mView.h + Ybound;
		//gCons->ConsPrintf("RIGHT\n");
	}
	SetCameraPos(ren, mView.x, mView.y);
	return 0;
}

bool Camera::EventProcess(Event eve)
{
	switch (*eve.GetEventType())
	{
	case CAMERA_TARGET:
		SetFollowTarget((Actor*)eve.GetEventData()->p);
		return true;
		break;
	default:
		gCons->ConsPrintf("Camera Received Unrecognized Event\n");
		return false;
		break;
	}
}