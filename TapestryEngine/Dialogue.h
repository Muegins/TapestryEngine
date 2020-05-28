#ifndef DIALOGUE_H
#define DIALOGUE_H

#include "Utils.h"
#include "Console.h"
#include "HUD.h"

#define DIALOGUE_LINES 4
#define CHAR_PER_LINE 30
#define DIALOGUE_CHAR_LIM (DIALOGUE_LINES * CHAR_PER_LINE)

struct DialogueLine
{
	SDL_Texture* LineTex;
	bool Displayed;
};

class Dialogue : public Widget, public EventReceiver //Must subscribe to the player to work
{
public:

	Dialogue() {}

	Dialogue(SDL_Rect pos, SDL_Renderer* ren, const char* font, char* text_box, SDL_Color fore, EventReceiver* player);

	bool TextWrap(int text_pix_max, const char* str);

	bool DialoguePrint();

	void CloseDialogue();

	bool EventProcess(Event eve);

	bool WidgetUpdate();

	bool WidgetDraw();

protected:

	EventReceiver* mPlayer;

	TTF_Font* mFont;

	SDL_Color mText_Color;

	std::vector<DialogueLine*> mLines_To_Print;
	int mline1;
	int mline2;

	WidgetElement mText_box;
};

#endif
