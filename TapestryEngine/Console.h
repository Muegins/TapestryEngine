#ifndef CONSOLE_H
#define CONSOLE_H

#include "Utils.h"


#define LINE_LIMIT 40
#define LINE_SIZE 100
#define CONSOLE_TEXT_LIMIT ((LINE_LIMIT+1)*LINE_SIZE)

class ConsoleStringManager
{
public:
	ConsoleStringManager();
	
	void AddLine(char* string, int CharCount);
	
	void ConsoleLog(char* msg);

	void ConsolePrintf(char* fmt, ...);

	char* GetLine(int x)
	{
		return mLines[x];
	}

	int GetNextLineIndex()
	{
		return mNextLineIndex;
	}

protected:

	char* mLines[LINE_LIMIT];
	int mNextLineIndex;

	char  mText[CONSOLE_TEXT_LIMIT];
	char* mEndPointer;


};

class Console
{
public:
	Console() {}

	Console(char* filename, int ptsize, SDL_Color Text, SDL_Color BG);

	void ConsPrintf(char* fmt, ...);

	void DrawConsole(SDL_Renderer* ren);

	void DrawConsoleReadout(SDL_Renderer* ren, int x, int y);
	
protected:
	TTF_Font* mFont;
	SDL_Color mText;
	SDL_Color mBG;
	SDL_Rect mTextRect;
	SDL_Rect mLinePosRect;
	ConsoleStringManager mCSM;
};


extern Console* gCons;

#endif