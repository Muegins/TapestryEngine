#ifndef DIAGNOSTICDRAW_H
#define DIAGNOSTICDRAW_H

#include "Utils.h"
#include "Console.h"
#include "Camera.h"
//#include "MiscDraw.h"


class DiagnosticDraw
{
public:

	DiagnosticDraw(SDL_Renderer* ren, Camera& cam) : mRen(ren), mCam(cam) {};

	void LogDiagRect(SDL_Rect rect)
	{
		mRectQueue.push_back(rect);
	}

	void LogPixel(int x, int y)
	{
		SDL_Rect pix;
		pix.h = 1;
		pix.w = 1;
		pix.x = x;
		pix.y = y;
		LogDiagRect(pix);
	}

	bool Update()
	{
		for (unsigned int i = 0; i < mRectQueue.size(); i++)
		{
			DrawRect(mRectQueue.at(i));
		}
		mRectQueue.clear();
		return true;
	}


protected:

	bool DrawRect(SDL_Rect WrldPos);

	std::vector<SDL_Rect> mRectQueue;
	Camera& mCam;
	SDL_Renderer* mRen;
};

extern DiagnosticDraw* gDiagDraw;

#endif
