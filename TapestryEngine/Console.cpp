#include "Console.h"


Console* gCons = NULL;

ConsoleStringManager::ConsoleStringManager()
{
	mEndPointer = mText;
	mNextLineIndex = 0;
	memset(mLines, 0, sizeof(mLines));
}

void ConsoleStringManager::AddLine(char* string, int CharCount)
{
	if (((mEndPointer - mText) + CharCount + 1) > CONSOLE_TEXT_LIMIT)
	{
		mEndPointer = mText;
	}
	
	memcpy(mEndPointer, string, CharCount);
	mEndPointer[CharCount] = '\0';

	mLines[mNextLineIndex] = mEndPointer;
	mEndPointer = (mEndPointer + CharCount + 1);
	
	mNextLineIndex = mNextLineIndex + 1;
	if (mNextLineIndex == LINE_LIMIT)
	{
		mNextLineIndex = 0;
	}
}

void ConsoleStringManager::ConsoleLog(char* msg)
{
	while (1)
	{
		char* TermChar = strchr(msg, '\n');
		if (TermChar == NULL) break;
	
		AddLine(msg, (TermChar - msg));
		msg = TermChar + 1;
	}	
}

void ConsoleStringManager::ConsolePrintf(char* fmt, ...)
{
	char msgf[256];

	va_list args;
	va_start(args, fmt);
	sprintf(msgf, fmt, args);
	va_end(args);
	
	ConsoleLog(msgf);
}

Console::Console(const char* filename, int ptsize, SDL_Color Text, SDL_Color BG)
{
	mTextRect.w = 0;
	mTextRect.h = 0;
	mTextRect.x = 0;
	mTextRect.y = 0;

	mLinePosRect.w = 0;
	mLinePosRect.h = 0;
	mLinePosRect.x = 0;
	mLinePosRect.y = 0;

	mFont = LoadFont(filename, ptsize);

	mText = Text;
	mBG = BG;
}

void Console::ConsPrintf(const char* fmt, ...)
{
	char msgf[256];

	va_list args;
	va_start(args, fmt);
	vsprintf(msgf, fmt, args);
	va_end(args);

	mCSM.ConsoleLog(msgf);
}

void Console::DrawConsole(SDL_Renderer* ren)
{

	int PrintIndex = mCSM.GetNextLineIndex();

	for (int i = 0; i < LINE_LIMIT; i++)
	{

		int NextLineIndex = (PrintIndex + i);
		if (NextLineIndex >= LINE_LIMIT)
		{
			NextLineIndex = NextLineIndex - LINE_LIMIT;
		}

		char* line = mCSM.GetLine(NextLineIndex);

		if (line != NULL)
		{
			const char* error;

			SDL_Surface* LineSur = TTF_RenderText_Shaded(mFont, line, mText, mBG);
			if (!LineSur)
			{
				error = SDL_GetError();
			}
			SDL_Texture* LineTex = SDL_CreateTextureFromSurface(ren, LineSur);
			if (!LineTex)
			{
				error = SDL_GetError();
			}
			SDL_FreeSurface(LineSur);
			if (SDL_QueryTexture(LineTex, NULL, NULL, &mTextRect.w, &mTextRect.h))
			{
				error = SDL_GetError();
			}

			mLinePosRect.w = mTextRect.w;
			mLinePosRect.h = mTextRect.h;
			mLinePosRect.x = 0;
			mLinePosRect.y = (mTextRect.h * i);

			if (SDL_RenderCopy(ren, LineTex, &mTextRect, &mLinePosRect))
			{
				error = SDL_GetError();
			}
			SDL_DestroyTexture(LineTex);
		}
	}
}

void Console::DrawConsoleReadout(SDL_Renderer* ren, int x, int y)
{
	int PrintIndex = mCSM.GetNextLineIndex();
	for (int i = 0; i < LINE_LIMIT; i++)
	{
		int NextLineIndex = (PrintIndex + i);
		if (NextLineIndex >= LINE_LIMIT)
		{
			NextLineIndex = NextLineIndex - LINE_LIMIT;
		}


		char* line = mCSM.GetLine(NextLineIndex);

		if (line != NULL)
		{
			const char* error;

			SDL_Surface* LineSur = TTF_RenderText_Shaded(mFont, line, mText, mBG);
			if (!LineSur)
			{
				error = SDL_GetError();
			}
			SDL_Texture* LineTex = SDL_CreateTextureFromSurface(ren, LineSur);
			if (!LineTex)
			{
				error = SDL_GetError();
			}
			SDL_FreeSurface(LineSur);
			if (SDL_QueryTexture(LineTex, NULL, NULL, &mTextRect.w, &mTextRect.h))
			{
				error = SDL_GetError();
			}

			mLinePosRect.w = mTextRect.w;
			mLinePosRect.h = mTextRect.h;
			mLinePosRect.x = x;
			mLinePosRect.y = y;

			if (SDL_RenderCopy(ren, LineTex, &mTextRect, &mLinePosRect))
			{
				error = SDL_GetError();
			}
			SDL_DestroyTexture(LineTex);
		}
	}
}
