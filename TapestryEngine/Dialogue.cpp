#include "Dialogue.h"

Dialogue::Dialogue(SDL_Rect pos, SDL_Renderer* ren, char* font, char* text_box, SDL_Color fore, EventReceiver* player) : Widget(ren, pos), mText_Color(fore)
{
	mPlayer = player;

	mDisplay = false; //In the case of the Dialogue widget mDisplay also tells if a dialogue is open.
	mFont = LoadFont(font, 20);

	mLines_To_Print.reserve(2);

	mText_box.img = SDL_CreateTextureFromSurface(ren, LoadSurfaceBMP(text_box));
	SDL_QueryTexture(mText_box.img, NULL, NULL, &mPos.w, &mPos.h);
	mText_box.pos = mPos;

	//TextWrap(390, "These Are Some Words. Here have a few more. Just Can't get enough little wordlings, seriously.");

	mline1 = 0;
	mline2 = 1;
}

bool Dialogue::TextWrap(int text_pix_max, char* str)
{
	int text_pix = -1;

	int size = strlen(str);
	char* text = (char*)malloc(size + 1);
	strcpy(text, str);
	text[size] = '\0';

	char* line = (char*)malloc(size + 1);
	memset(line, 0, sizeof(line));
	char* last_fit = (char*)malloc(size + 1);
	memset(last_fit, NULL, sizeof(last_fit));

	char* tok;
	tok = strtok(text, " ");
	while (tok != NULL)
	{
		strcat(line, tok);

		int h;
		TTF_SizeText(mFont, line, &text_pix, &h);
		if (text_pix >= text_pix_max)
		{
			if (last_fit == NULL)
			{
				return false;
			}

			DialogueLine* dline = new DialogueLine;
			SDL_Surface* sur = TTF_RenderText_Blended(mFont, last_fit, mText_Color);
			dline->LineTex = SDL_CreateTextureFromSurface(mren, sur);
			SDL_FreeSurface(sur);
			mLines_To_Print.push_back(dline);

			memset(line, 0, sizeof(line));
			strcat(line, tok);
			strcat(line, " ");
		}
		else
		{
			strcpy(last_fit, line);
			strcat(line, " ");
		}
		tok = strtok(NULL, " ");
	}

	DialogueLine* dline = new DialogueLine;
	SDL_Surface* sur = TTF_RenderText_Blended(mFont, last_fit, mText_Color);
	dline->LineTex = SDL_CreateTextureFromSurface(mren, sur);
	SDL_FreeSurface(sur);
	mLines_To_Print.push_back(dline);

	if (IsEven((int)mLines_To_Print.size()) == false)
	{
		DialogueLine* blank = new DialogueLine;
		blank->Displayed = false;
		SDL_Surface* blank_sur = TTF_RenderText_Blended(mFont, " ", mText_Color);
		blank->LineTex = SDL_CreateTextureFromSurface(mren, blank_sur);
		SDL_FreeSurface(blank_sur);
		mLines_To_Print.push_back(blank);
	}
	return true;
}

bool Dialogue::DialoguePrint()
{
	int j = 0;
	for (int i = 0; i < (int)mLines_To_Print.size(); i++)
	{
		if (mLines_To_Print.at(i)->Displayed == true)
		{
			SDL_Texture* tex = mLines_To_Print.at(i)->LineTex;
			SDL_Rect dst = mText_box.pos;
			SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);

			dst.x = mText_box.pos.x + 5;
			dst.y = mText_box.pos.y + 4 + (dst.h * j);

			SDL_RenderCopy(mren, tex, NULL, &dst);
			j++;
		}
	}
	//		mLines_To_Print.clear();
	return false;
}

void Dialogue::CloseDialogue()
{
	mPlayer->EventProcess(Event(TERMINATE_DIALOGUE));
	mDisplay = false;
	mLines_To_Print.clear();

	mline1 = 0;
	mline2 = 1;
}

bool Dialogue::EventProcess(Event eve)
{
	switch (*eve.GetEventType())
	{
	case DIALOGUE:
		if (mDisplay == false)
		{
			mDisplay = true;
			TextWrap(390, eve.GetEventData()->dd.str);
		}
		break;
	case SCROLL:
		if ((int)mLines_To_Print.size() > (mline2 + 1))
		{
			mline1+=2;
			mline2+=2;
		}
		else
		{
			CloseDialogue();
		}
		break;
	case TERMINATE_DIALOGUE: //Called to terminate dialogue early
		CloseDialogue();
		break;
	default:
		gCons->ConsPrintf("Unrecognized event sent to dialogue system\n");
	}
	return true;
}

bool Dialogue::WidgetUpdate()
{
	for (int i = 0; i < (int)mLines_To_Print.size(); i++)
	{
		mLines_To_Print.at(i)->Displayed = false;
	}
	if ((int)mLines_To_Print.size() > 0)
	{
		mLines_To_Print.at(mline1)->Displayed = true;
		mLines_To_Print.at(mline2)->Displayed = true;
	}

	return true;
}

bool Dialogue::WidgetDraw()
{
	if (mDisplay == true)
	{
		SDL_RenderCopy(mren, mText_box.img, NULL, &mText_box.pos);

		DialoguePrint();
	}
	return true;
}
