#include "HUD.h"

void CalcElementScreenPosition(Widget* wid, SDL_Rect elementRect)
{
	elementRect.x += wid->GetPos()->x;
	elementRect.y += wid->GetPos()->y;
};

bool HUD::LogWidget(Widget* wid)
{
	assert(mIndex < 10);
	mWidgets[mIndex] = wid;
	mIndex += 1;
	return true;
}

bool HUD::UpdateWidgets()
{
	for (int i = 0; i < mIndex; i++)
	{
		mWidgets[i]->WidgetUpdate();
	}
	return true;
}

bool HUD::DrawWidgets()
{
	for (int i = 0; i < mIndex; i++)
	{
		mWidgets[i]->WidgetDraw();
	}
	return true;
}

LifeMeter::LifeMeter(Player* target, SDL_Rect pos, SDL_Renderer* ren, char* life_base, char* life_bar) : Widget(ren, pos)
{
	mHPmax = target->GetMaxHP();
	mHP = target->GetHP();
	
	mBase.img    = SDL_CreateTextureFromSurface(mren, LoadSurfaceBMP(life_base));
	mLifebar.img = SDL_CreateTextureFromSurface(mren, LoadSurfaceBMP(life_bar ));

	mBase.pos      = mPos;
	mLifebar.pos.x = 0;
	mLifebar.pos.y = 0;
	mLifebar.pos.h = mPos.h;
	mLifebar.pos.w = mPos.w;
}

bool LifeMeter::WidgetUpdate()
{
	mLifebar.pos.w = (int)( (mBase.pos.w)*(( (float)(*mHP) ) / ( (float)(*mHPmax)) ) );
	return true;
}

bool LifeMeter::WidgetDraw()
{
	SDL_RenderCopy(mren, mBase.img, NULL, &mBase.pos);
	CalcElementScreenPosition(this, mLifebar.pos);
	SDL_RenderCopy(mren, mLifebar.img, NULL, &mLifebar.pos);
	return true;
}
//

//Fader
Fader::Fader(SDL_Renderer* ren, char* black, char* red) : Widget(ren, { 0,0,0,0 })
{
	mDisplay = false;

	mBlack.img = SDL_CreateTextureFromSurface(mren, LoadSurfaceBMP(black));
	mRed.img = SDL_CreateTextureFromSurface(mren, LoadSurfaceBMP(red));

	mBlack.pos = mPos;
}

void Fader::PlayFade(int duration, int color, int opacity)
{
	mDisplay = true;
	mOpacity = 0;

	mOpacityTarget = opacity;
	mFadeColor = color;
	mTimer = gTime->GetCurrentCycle();
	mFadeTime = duration / 2;
}

bool Fader::WidgetUpdate()
{
	if (mDisplay == true)
	{
		if (gTime->GetCurrentCycle() - mTimer <= mFadeTime) //if the timer is less than the fade-in/out time 
		{
			mOpacity = (int)( ((float)(gTime->GetCurrentCycle() - mTimer) / (float)mFadeTime) * (float)mOpacityTarget );
		}
		else if (gTime->GetCurrentCycle() - mTimer <= 2 * mFadeTime) //if the time is not less then the fade time, but is less than the total time
		{
			mOpacity = (int)( ((float)mFadeTime / (float)(gTime->GetCurrentCycle() - mTimer)) * (float)mOpacityTarget );
		}
		else //if the timer is over the fade time
		{
			mDisplay = false;
		}
	}
	
	return true;
}

bool Fader::WidgetDraw()
{
	if (mDisplay == true)
	{
		switch (mFadeColor)
		{
		case FADE_BLACK:
			SDL_RenderCopy(mren, mBlack.img, NULL, NULL);
			SDL_SetTextureAlphaMod(mBlack.img, mOpacity);
			break;
		case FADE_RED:
			SDL_RenderCopy(mren, mRed.img, NULL, NULL);
			SDL_SetTextureAlphaMod(mRed.img, mOpacity);
			break;
		default:
			gCons->ConsPrintf("Unknown fade color\n");
		}
	}
	return true;
}

bool Fader::EventProcess(Event eve)
{
	switch (*eve.GetEventType())
	{
	case FADE:
		PlayFade(eve.GetEventData()->fd.duration, eve.GetEventData()->fd.color, eve.GetEventData()->fd.opacity);
		break;
	case TERMINATE_DIALOGUE:
	case SCROLL:
	case DIALOGUE:
		break;
	default:
		gCons->ConsPrintf("Fader received unrecognized event\n");
		return false;
		break;
	}
	return true;
}
//
