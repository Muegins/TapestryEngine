#ifndef HUD_H
#define HUD_H

#include "Utils.h"
#include "Console.h"
#include "Actor.h"
#include "MiscDraw.h"
#include "Event.h"


struct WidgetElement
{
	SDL_Rect pos;
	SDL_Texture* img;
};

class Widget
{
public:

	Widget() {}

	Widget(SDL_Renderer* ren, SDL_Rect pos) : mPos(pos), mren(ren), mDisplay(true)
	{
	}

	SDL_Rect* GetPos()
	{
		return &mPos;
	}

	virtual bool WidgetUpdate() = 0;

	virtual bool WidgetDraw() = 0;

protected:

	bool mDisplay;
	SDL_Renderer* mren;
	SDL_Rect mPos;

};

struct SDL_Rect CalcElementScreenPosition(Widget* wid, SDL_Rect elementRect);

class LifeMeter : public Widget
{
public:

	LifeMeter() {}

	LifeMeter(Player* target, SDL_Rect pos, SDL_Renderer* ren, char* life_base, char* life_bar);

	bool WidgetUpdate();

	bool WidgetDraw();

protected:

	int* mHP;
	int* mHPmax;
	WidgetElement mBase;
	WidgetElement mLifebar;

};

class Fader : public Widget, public EventReceiver //Must Subscribe to the player
{
public:
	Fader() {}

	Fader(SDL_Renderer* ren, char* black, char* red);

	void PlayFade(int duration,int color, int opacity);

	bool WidgetUpdate();

	bool WidgetDraw();

	bool EventProcess(Event eve);

protected:

	WidgetElement mBlack;
	WidgetElement mRed;

	int mOpacityTarget;
	int mFadeTime;
	int mFadeColor;

	int mTimer;
	int mOpacity;
};

class HUD
{
public:

	HUD() : mIndex(0) {}

	bool LogWidget(Widget* wid);

	bool UpdateWidgets();

	bool DrawWidgets();

protected:

	Widget* mWidgets[10];
	int mIndex;
};



#endif
