#include "DiagnosticDraw.h"

DiagnosticDraw* gDiagDraw = NULL;

bool DiagnosticDraw::DrawRect(SDL_Rect WrldPos)
{
	SDL_Rect ScreenPos;
	ScreenPos.h = (int)((float)(WrldPos.h)*((float)(SCREEN_H) / (float)(mCam.GetCamView()->h)));
	ScreenPos.w = (int)((float)(WrldPos.w)*((float)(SCREEN_W) / (float)(mCam.GetCamView()->w)));

	ScreenPos.x = (int)((float)(WrldPos.x - mCam.GetCamX())*((float)(SCREEN_W) / (float)(mCam.GetCamView()->w)));
	ScreenPos.y = (int)((float)(WrldPos.y - mCam.GetCamY())*((float)(SCREEN_H) / (float)(mCam.GetCamView()->h)));

	SDL_Point pts[5];
	pts[0].x = ScreenPos.x;
	pts[0].y = ScreenPos.y;
	pts[1].x = ScreenPos.x + ScreenPos.w;
	pts[1].y = ScreenPos.y;
	pts[2].x = ScreenPos.x + ScreenPos.w;
	pts[2].y = ScreenPos.y + ScreenPos.h;
	pts[3].x = ScreenPos.x;
	pts[3].y = ScreenPos.y + ScreenPos.h;
	pts[4].x = ScreenPos.x;
	pts[4].y = ScreenPos.y;

	SDL_RenderDrawLines(mRen, pts, 5);

	return false;
}
