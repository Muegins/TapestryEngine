#include <time.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdarg.h>
#include "SDL.h"
#include "SDL_ttf.h"

//Time Defines
#define FRAMES_PER_SECOND 60.0
#define CLOCKS_PER_FRAME (CLOCKS_PER_SEC/FRAMES_PER_SECOND)
#define MS_PER_FRAME 1/(FRAMES_PER_SECOND/1000)
//

//World/Screen size defines
#define WORLD_W 1920
#define WORLD_H 1080

#define SCREEN_W 1280
#define SCREEN_H 720
//

// Console Defines
#define LINE_LIMIT 40
#define LINE_SIZE 100
#define CONSOLE_TEXT_LIMIT ((LINE_LIMIT+1)*LINE_SIZE)
//

//Actor Direction Defines
#define LEFT  1
#define RIGHT 0
//

//Actor State Defines
#define IDLE      10
#define RUN		  20

#define RUN_LEFT  1
#define RUN_RIGHT 2
#define RUN_DOWN  3
#define RUN_UP    4
//

//Terrain type defines
#define AIR			0x00
#define GROUND		0x01
#define PLATFORM	0x02
#define WATER		0x04

class Console;
Console* gCons = NULL;
Console* rCons = NULL;

class ConsoleStringManager
{
public:
	ConsoleStringManager()
	{
		mEndPointer = mText;
		mNextLineIndex = 0;
		memset(mLines, 0, sizeof(mLines));
	}

	void AddLine(char* string, int CharCount)
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

	void ConsoleLog(char* msg)
	{
		while (1)
		{
			char* TermChar = strchr(msg, '\n');
			if (TermChar == NULL) break;

			AddLine(msg, (TermChar - msg));
			msg = TermChar + 1;
		}
	}

	void ConsolePrintf(char* fmt, ...)
	{
		char msgf[256];

		va_list args;
		va_start(args, fmt);
		sprintf(msgf, fmt, args);
		va_end(args);

		ConsoleLog(msgf);
	}

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
	Console(char* filename, int ptsize, SDL_Color Text, SDL_Color BG)
	{
		mTextRect.w = 0;
		mTextRect.h = 0;
		mTextRect.x = 0;
		mTextRect.y = 0;

		mLinePosRect.w = 0;
		mLinePosRect.h = 0;
		mLinePosRect.x = 0;
		mLinePosRect.y = 0;

		char* basepath = "C:\\Users\\baptistac1\\Documents\\Visual Studio 2013\\Projects\\TapestryEngine\\TapestryEngine\\fonts\\";

		char pathbuffer[1024];
		strcpy(pathbuffer, basepath);
		char* fullpath = strcat(pathbuffer, filename);

		mFont = TTF_OpenFont(fullpath, ptsize);

		assert(mFont != NULL);

		mText = Text;
		mBG = BG;
	}

	void ConsPrintf(char* fmt, ...)
	{
		char msgf[256];

		va_list args;
		va_start(args, fmt);
		vsprintf(msgf, fmt, args);
		va_end(args);

		mCSM.ConsoleLog(msgf);
	}

	void DrawConsole(SDL_Renderer* ren)
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

	void DrawConsoleReadout(SDL_Renderer* ren, int x,int y)
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
protected:
	TTF_Font* mFont;
	SDL_Color mText;
	SDL_Color mBG;
	SDL_Rect mTextRect;
	SDL_Rect mLinePosRect;
	ConsoleStringManager mCSM;
};

int GetTimeF() //measures in frames
{
	int time = (clock() / CLOCKS_PER_FRAME);
	return time;
}

int GetTimeMS() //measures in milliseconds
{
	int time = (clock() / (CLOCKS_PER_SEC/1000));
	return time;
}

SDL_Surface* LoadSurfaceBMP(const char* filename)
{
	char* basepath = "C:\\Users\\baptistac1\\Documents\\Visual Studio 2013\\Projects\\TapestryEngine\\TapestryEngine\\imgs\\";

	char pathbuffer[1024];
	strcpy(pathbuffer, basepath);

	SDL_Surface* surface = SDL_LoadBMP(strcat(pathbuffer, filename));
	if (surface == NULL)
	{
		gCons->ConsPrintf("SDL_LoadBMP Error: %s", SDL_GetError());
	}

	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0xFF, 0x00, 0xFF));

	return surface;
}

struct Frame
{
	SDL_Rect FrameRect;
	SDL_Texture* FrameSource;
};

class FrameSet
{
public:
	FrameSet() : mFrameCount(0), mFrames() {}

	FrameSet(SDL_Renderer* ren, const char* SourcePath, int FrameCount, int FRate, int frameH, int frameW)
	{
		memset(mFrames, 0, 256);
		mframesource = SDL_CreateTextureFromSurface(ren,LoadSurfaceBMP(SourcePath));
		mFrameCount = (FrameCount - 1);
		mDefaultFrameRate = FRate;

		SDL_Rect framerect;
		framerect.h = frameH;
		framerect.w = frameW;
		framerect.x = 0;
		framerect.y = 0;

		int i = 0;
		while (i <= mFrameCount)
		{
			
			framerect.x = ((i)*frameW);
			
			mFrames[i] = framerect;

			i++;
		}
	}

	int GetNumberOfFrames()
	{
		return mFrameCount;
	}

	int GetDefaultFrameRate()
	{
		return mDefaultFrameRate;
	}

	SDL_Texture* GetFrameSource()
	{
		return mframesource;
	}

	SDL_Rect GetFrameRect(int framenumber)
	{
		//gCons->ConsPrintf("Frame Number = %i\n", framenumber);
		return mFrames[framenumber];
	}

protected:
	int mFrameCount;
	int mDefaultFrameRate;
	SDL_Texture* mframesource;
	SDL_Rect mFrames[256];
};

class animation
{
public:

	animation() : mFrameSet(), mCurrentFrameNumber(0) {}

	animation(FrameSet* set, bool flip = true)
	{
		mFrameSet = set;
		mCurrentFrameNumber = 0;
		mFrameRate = set->GetDefaultFrameRate();
		mTimer = 0;
		mIsFlippable = flip;
		mIsPlaying = false;
		mCurrentFrame.FrameSource = mFrameSet->GetFrameSource();
		mCurrentFrame.FrameRect = mFrameSet->GetFrameRect(mCurrentFrameNumber);
	}

	Frame GetCurrentFrame()
	{
		mCurrentFrame.FrameRect = mFrameSet->GetFrameRect(mCurrentFrameNumber);
		if (mIsPlaying == true)
		{
			if ((GetTimeMS() - mTimer) >= mFrameRate)
			{
				if (mCurrentFrameNumber == mFrameSet->GetNumberOfFrames())
				{
					mCurrentFrameNumber = 0;
				}
				else
				{
					mCurrentFrameNumber = (mCurrentFrameNumber + 1);
				}
				mTimer = GetTimeMS();
			}
		}
		return mCurrentFrame;
	}

	bool SetPlaySpeed(int speed)
	{
		mFrameRate = speed;
	}

	bool IsFlippable()
	{
		return mIsFlippable;
	}

	bool Play()
	{
		return mIsPlaying = true;
	}
	bool Stop()
	{
		mCurrentFrameNumber = 0;
		return mIsPlaying = false;
	}

protected:

	FrameSet* mFrameSet;
	int mCurrentFrameNumber;
	Frame mCurrentFrame;
	int mTimer;
	int mFrameRate;
	bool mIsFlippable;
	bool mIsPlaying;
};

class animPack
{
public:
	animPack() : mIndexer(), mAnimData() {}

	animPack(int AnimCount, FrameSet** AnimData, int* Index)
	{
		mAnimData   = AnimData;
		mIndexer = Index;
		mAnimCount = AnimCount;

		mAnims = new animation[AnimCount];
		for ( int i = 0; i < mAnimCount; i++)
		{
			mAnims[i] = animation( mAnimData[i] );
		}
	}

	FrameSet* GetAnimationData(int AnimationID)
	{
		for (int i = 0; i < mAnimCount; i++)
		{
			if (mIndexer[i] == AnimationID)
			{
				return mAnimData[i];
			}
		}
	}

	animation* GetAnimation(int AnimationID)
	{
		for (int i = 0; i < mAnimCount; i++)
		{
			if (mIndexer[i] == AnimationID)
			{
				if (mLastIndex != i)
				{
					mAnims[mLastIndex].Stop();
					mLastIndex = i;
				}

				mAnims[i].Play();
				return &mAnims[i];
			}
		}
	}

protected:

	int		    mAnimCount;
	int*        mIndexer;
	int			mLastIndex;
	FrameSet**  mAnimData;
	animation*  mAnims;
};


class Terrain
{
public:
	Terrain(SDL_Surface* Col_Map)
	{
		mCol_Map = Col_Map;
	}

	bool DetectGroundIntersect(SDL_Rect* Bounds)
	{
		if (mCol_Map->format->format != SDL_PIXELFORMAT_INDEX8)
		{
			gCons->ConsPrintf("Non-INDEX8 Collision Map Detected\n");
		}

		Uint8* PixMap = (Uint8*)mCol_Map->pixels;
		if (Bounds->y < 0)
		{
			Bounds->y = 0;
		}
		for (int y = Bounds->y; y <= (Bounds->y + Bounds->h); y++)
		{
			if (Bounds->x < 0)
			{
				Bounds->x = 0;
			}
			for (int x = Bounds->x; x <= (Bounds->x + Bounds->w); x++)
			{
				if (PixMap[(y*mCol_Map->w) + x] == GROUND)
				{
					//gCons->ConsPrintf("ground collision detected \n");
					return true;
				}
				else
				{
					//gCons->ConsPrintf("no collision detected \n");
				}
			}
		}
		return false;
	}

	bool DetectEdgeCollision(SDL_Rect* Bounds, int EdgeThickness)
	{
		//SDL_Rect LowerBounder;
		LowerBounder.w = Bounds->w;
		LowerBounder.x = Bounds->x;
		LowerBounder.h = EdgeThickness;
		LowerBounder.y = ((Bounds->y + Bounds->h) - EdgeThickness );

		//SDL_Rect UpperBounder;
		UpperBounder.w = Bounds->w;
		UpperBounder.x = Bounds->x;
		UpperBounder.h = EdgeThickness;
		UpperBounder.y = Bounds->y;

		//SDL_Rect RightBounder;
		RightBounder.w = EdgeThickness;
		RightBounder.x = ((Bounds->x + Bounds->w) - EdgeThickness);
		RightBounder.h = Bounds->h;
		RightBounder.y = Bounds->y;

		//SDL_Rect LeftBounder;
		LeftBounder.w = EdgeThickness;
		LeftBounder.x = Bounds->x;
		LeftBounder.h = Bounds->h;
		LeftBounder.y = Bounds->y;

		if ((DetectGroundIntersect(&LowerBounder) == true) ||
			(DetectGroundIntersect(&UpperBounder) == true) ||
			(DetectGroundIntersect(&RightBounder) == true) ||
			(DetectGroundIntersect(&LeftBounder ) == true)  )
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	SDL_Rect LeftBounder;
	SDL_Rect RightBounder;
	SDL_Rect UpperBounder;
	SDL_Rect LowerBounder;
protected:

	SDL_Surface* mCol_Map;

};

class Actor
{
public:

	Actor() : mTex(), mHeight(0), mWidth(0), mX(0), mY(0) {}

	Actor(SDL_Renderer* ren, Terrain* ter, animPack Anims, char* file, int Height, int Width, int X, int Y)
	{
		mTerrain = ter;
		SDL_Surface* surface = LoadSurfaceBMP(file);
		mTex = SDL_CreateTextureFromSurface(ren, surface); 
		mAnimPack = Anims;
		mHeight = Height;
		mWidth = Width;
		mX = X;
		mY = Y;
		mState = IDLE;
	}

	int MoveActorCollision(float xspd, float yspd)
	{
		SDL_Rect Destination;
		Destination.h = mHeight;
		Destination.w = mWidth;
		Destination.x = (int)( (float)mX + (xspd*(GetTimeF() - mLastMoveUpdate)) );
		Destination.y = (int)( (float)mY + (yspd*(GetTimeF() - mLastMoveUpdate)) );
	
		
		if (mTerrain->DetectEdgeCollision(&Destination,5) == true)
		{
			MoveActorCollision( (int)((xspd)*(0.5)), (int)((yspd)*(0.5)) );
		}
		else
		{
			mX = Destination.x;
			mY = Destination.y;
		}
		mLastMoveUpdate = GetTimeF();
		return 0;
	}

	int MoveActor(float xspd, float yspd)
	{
		mX = mX + xspd*(GetTimeF() - mLastMoveUpdate);
		mY = mY + yspd*(GetTimeF() - mLastMoveUpdate);
		mLastMoveUpdate = GetTimeF();
		return 0;
	}

	int walk(int spd)
	{
		
		if (mDir == RIGHT)
		{
			MoveActorCollision( spd, 0);
		}
		else //mDIR == LEFT
		{
			MoveActorCollision(-spd, 0);
		}
		MoveActorCollision(0, 4);
		return 0;
	}

	bool ControlActor(int xspd, int yspd, SDL_Event* eve)
	{
		if (eve->key.type == SDL_KEYUP)
		{
			mState = IDLE;
			return 0;
		}

		switch (eve->key.keysym.sym)
		{
		case  SDLK_DOWN:
			mState = RUN_DOWN;
			break;
		case    SDLK_UP:
			mState = RUN_UP;
			break;
		case  SDLK_LEFT:
			mState = RUN_LEFT;
			mDir = LEFT;
			break;
		case SDLK_RIGHT:
			mState = RUN_RIGHT;
			mDir = RIGHT;
			break;
		}


		//mLastMoveUpdate = GetTimeF();
		return 0;
	}

	bool ActorUpdate()
	{
		int xspd = 3;
		int yspd = 3;
		
		switch (mState)
		{
		case RUN_DOWN:
			MoveActorCollision(0, yspd);
			mFrame = mAnimPack.GetAnimation(RUN)->GetCurrentFrame();
			//gCons->ConsPrintf("down\n");
			break;
		case RUN_UP:
			MoveActorCollision(0, -yspd);
			mFrame = mAnimPack.GetAnimation(RUN)->GetCurrentFrame();
			//gCons->ConsPrintf("up\n");
			break;
		case RUN_LEFT:
			walk(xspd);
			mFrame = mAnimPack.GetAnimation(RUN)->GetCurrentFrame();
			//gCons->ConsPrintf("left\n");
			break;
		case RUN_RIGHT:
			walk(xspd);
			mFrame = mAnimPack.GetAnimation(RUN)->GetCurrentFrame();
			//gCons->ConsPrintf("right\n");
			break;
		case IDLE:
			mFrame = mAnimPack.GetAnimation(IDLE)->GetCurrentFrame();
			//gCons->ConsPrintf("idle\n");
			mLastMoveUpdate = GetTimeF();
			break;
		default:
			return false;
		}
		return true;
	}

	int GetX()
	{
		return mX;
	}

	int GetY()
	{
		return mY;
	}

	int GetHeight()
	{
		return mHeight;
	}

	int GetWidth()
	{
		return mWidth;
	}

	SDL_Rect GetRect()
	{
		SDL_Rect Bounds;
		Bounds.x = mX;
		Bounds.y = mY;
		Bounds.h = mHeight;
		Bounds.w = mWidth;

		return Bounds;
	}

	SDL_Texture* GetTex()
	{
		return mTex;
	}

	Frame GetFrame()
	{
		return mFrame;
	}

	int GetState()
	{
		return mState;
	}

	int GetDir()
	{
		return mDir;
	}

protected:
	
	SDL_Texture* mTex;
	Terrain* mTerrain;
	animPack mAnimPack;
	Frame mFrame;
	int mState;
	int mDir;
	int mHeight;
	int mWidth;
	int mX;
	int mY;
	int mLastMoveUpdate;
};


class Camera
{
public:
	Camera() : view(), wrldX(), wrldY()  {}

	Camera(int H, int W, int X, int Y)
	{
		view.h = H;
		view.w = W;

		wrldX = X;
		wrldY = Y;
		view.x = wrldX;
		view.y = wrldY;
	}

	int GetCamX()
	{
		return wrldX;
	}

	int GetCamY()
	{
		return wrldY;
	}

	SDL_Rect* GetCamView()
	{
		return &view;
	}

	void CamResize(int H, int W)
	{
		view.h = H;
		view.w = W;
	}

	SDL_Rect SetCameraPos(SDL_Renderer* ren, int Xpos, int Ypos)
	{
		wrldX = Xpos;
		wrldY = Ypos;

		if (Xpos < 0)
		{
			wrldX = 0;
		}
		else if ( (Xpos + view.w) > WORLD_W)
		{
			wrldX = WORLD_W - view.w;
		}

		if (Ypos < 0)
		{
			wrldY = 0;
		}
		else if ((Ypos + view.h) > WORLD_H)
		{
			wrldY = WORLD_H - view.h;
		}

		view.x = wrldX;
		view.y = wrldY;

		//gCons->ConsPrintf("cam bounds: x= %i - %i, y= %i - %i \n", view.x, (view.x + view.w), view.y, (view.y + view.h));

		return view;
	}

	SDL_Rect SetCameraPosUnbounded(SDL_Renderer* ren, int Xpos, int Ypos)
	{
		wrldX = Xpos;
		wrldY = Ypos;

		view.x = wrldX;
		view.y = wrldY;

		//gCons->ConsPrintf("cam bounds: x= %i - %i, y= %i - %i \n", view.x, (view.x + view.w), view.y, (view.y + view.h));

		return view;
	}

	bool ArrowKeyMove(SDL_Renderer* ren, int xspd, int yspd, SDL_Event* eve)
	{
		if (eve->key.type == SDL_KEYUP) return 0;

		switch (eve->key.keysym.sym)
		{
		case  SDLK_DOWN: 
			wrldY = wrldY + yspd;
			break;
		case    SDLK_UP: 
			wrldY = wrldY + -yspd;
			break;
		case  SDLK_LEFT: 
			wrldX = wrldX + -xspd;
			break;
		case SDLK_RIGHT: 
			wrldX = wrldX + xspd;
			break;
		}
		mLastMoveUpdate = GetTimeF();
		SetCameraPos(ren, wrldX, wrldY);
		return 0;
	}

	bool ActorFollow(SDL_Renderer* ren, Actor act, int Xbound, int Ybound)
	{
		if (act.GetX() < (wrldX + Xbound))
		{
			wrldX = (act.GetX() - Xbound);
			//gCons->ConsPrintf("LEFT\n");
		}
		if (act.GetX() + act.GetWidth() > ((wrldX + view.w) - Xbound))
		{
			wrldX = act.GetX() + act.GetWidth() - view.w + Xbound ;
			//gCons->ConsPrintf("RIGHT\n");
		}
		
		if (act.GetY() < (wrldY + Ybound))
		{
			wrldY = (act.GetY() - Ybound);
			//gCons->ConsPrintf("LEFT\n");
		}
		if (act.GetY() + act.GetHeight() > ((wrldY + view.h) - Ybound))
		{
			wrldY = act.GetY() + act.GetHeight() - view.h + Ybound;
			//gCons->ConsPrintf("RIGHT\n");
		}
		mLastMoveUpdate = GetTimeF();
		SetCameraPos(ren, wrldX, wrldY);
		return 0;
	}

protected:
	SDL_Rect view;
	int wrldX;
	int wrldY;
	int mLastMoveUpdate;
};

SDL_Rect GetScreenPos(Actor act, Camera cam)
{
	SDL_Rect ScreenPos;
	ScreenPos.h = (int)((float)(act.GetHeight())*((float)(SCREEN_H) / (float)( cam.GetCamView()->h )));
	ScreenPos.w = (int)((float)(act.GetWidth())*((float)(SCREEN_W) / (float)( cam.GetCamView()->w )));

	ScreenPos.x = (int)((float)(act.GetX() - cam.GetCamX())*((float)(SCREEN_W) / (float)( cam.GetCamView()->w )));
	ScreenPos.y = (int)((float)(act.GetY() - cam.GetCamY())*((float)(SCREEN_H) / (float)( cam.GetCamView()->h )));

	return ScreenPos;
}

SDL_Rect DrawActorTex(SDL_Renderer* ren, Actor act, Camera cam)
{
	SDL_Rect ScreenPos = GetScreenPos(act, cam);
	
	SDL_RenderCopy(ren, act.GetTex(), NULL, &ScreenPos);
	return ScreenPos;
}

SDL_Rect DrawActorAnim(SDL_Renderer* ren, Actor act, animation* anim, Camera cam, int dir)
{
	SDL_Rect ScreenPos = GetScreenPos(act, cam);

	Frame RenderFrame = anim->GetCurrentFrame();

	SDL_RendererFlip flip;

	if (anim->IsFlippable() == true)
	{
		flip = (SDL_RendererFlip)act.GetDir();
	}
	else
	{
		flip = SDL_FLIP_NONE;
	}
	SDL_RenderCopyEx(ren, RenderFrame.FrameSource, &(RenderFrame.FrameRect), &ScreenPos, 0, NULL, flip);

	return ScreenPos;
}

SDL_Rect DrawActor(SDL_Renderer* ren, Actor act, Camera cam)
{
	SDL_Rect ScreenPos = GetScreenPos(act, cam);

	Frame RenderFrame = act.GetFrame();

	SDL_RendererFlip flip;
	flip = (SDL_RendererFlip)act.GetDir();
	
	SDL_RenderCopyEx(ren, RenderFrame.FrameSource, &(RenderFrame.FrameRect), &ScreenPos, 0, NULL, flip);

	return ScreenPos;
}

bool DrawRect(SDL_Renderer* ren, SDL_Rect WrldPos, Camera cam)
{
	SDL_Rect ScreenPos;
	ScreenPos.h = (int)((float)(WrldPos.h)*((float)(SCREEN_H) / (float)(cam.GetCamView()->h)));
	ScreenPos.w = (int)((float)(WrldPos.w)*((float)(SCREEN_W) / (float)(cam.GetCamView()->w)));

	ScreenPos.x = (int)((float)(WrldPos.x - cam.GetCamX())*((float)(SCREEN_W) / (float)(cam.GetCamView()->w)));
	ScreenPos.y = (int)((float)(WrldPos.y - cam.GetCamY())*((float)(SCREEN_H) / (float)(cam.GetCamView()->h)));

	SDL_Surface* Bounds    = LoadSurfaceBMP("BoundingBox.bmp");
	SDL_Texture* BoundsTex = SDL_CreateTextureFromSurface(ren, Bounds);

	SDL_RenderCopy(ren, BoundsTex, NULL, &ScreenPos);

	return false;
}

int main(int argc, char *argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO & SDL_INIT_EVENTS) != 0)
	{
		gCons->ConsPrintf("SDL_Init Error: %s\n", SDL_GetError());
		SDL_Quit();
		return 1;
	}

	if (TTF_Init() != 0)
	{
		gCons->ConsPrintf("TTF_Init Error: %s\n", TTF_GetError());
		TTF_Quit();
		SDL_Quit();
		return 1;
	}
	
	SDL_Window* window = SDL_CreateWindow("Bandana Marathon", 10, 30, SCREEN_W, SCREEN_H, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		gCons->ConsPrintf("SDL_CreateWindow Error: %s", SDL_GetError());
		SDL_Quit();
		return 1;
	}
	
	SDL_Color fg = { 255, 255, 255 };
	SDL_Color bg = { 0, 0, 255 };
	
	gCons = new Console("ARIAL.TTF", 12, fg, bg);
	rCons = new Console("ARIAL.TTF", 12, fg, bg);

	Camera cam = Camera(468, 832, 700, 0);

	SDL_Renderer* ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren == NULL)
	{
		gCons->ConsPrintf("SDL_CreateRenderer Error: %s", SDL_GetError());
		SDL_Quit();
		return 1;
	}

	FrameSet  RunManSet     = FrameSet(ren, "BandanaManRun.bmp", 14, 50, 150, 75);
	animation RunMan        = animation(&RunManSet, 1000);
	FrameSet  RunManPlusSet = FrameSet(ren, "BandanaManPlus.bmp", 14, 50, 150, 75);
	animation RunManPlus    = animation(&RunManPlusSet, 50);
	FrameSet  RunWomanSet	= FrameSet(ren, "BandanaWomanRun.bmp", 14, 50, 150, 75);
	animation RunWoman      = animation(&RunWomanSet, 50);
	
	
	FrameSet  PlayerRunSet = FrameSet(ren, "player_run.bmp", 15, 50, 30, 30);
	FrameSet  PlayerTempIdle = FrameSet(ren, "player_idle_standin.bmp", 15, 50, 30, 30);

	//NULL Animation Pack Construction
	int NULL_AnimCount = 2;
	FrameSet** NullPack = (FrameSet**)malloc(NULL_AnimCount * sizeof(FrameSet*));
	int* NullIndex = (int*)malloc(NULL_AnimCount * sizeof(int));
	NullPack[0] = &PlayerTempIdle;
	NullPack[1] = &PlayerRunSet;
	NullIndex[0] = IDLE;
	NullIndex[1] = RUN;
	animPack NULLPack = animPack(NULL_AnimCount, NullPack, NullIndex);
	//

	//Player Animation Pack Construction
	int Player_AnimCount = 2;
	FrameSet** PlayerAnimPack = (FrameSet**)malloc(Player_AnimCount * sizeof(FrameSet*));
	int* PlayerIndex = (int*)malloc(Player_AnimCount * sizeof(int));
	PlayerAnimPack[0] = &PlayerTempIdle;
	PlayerAnimPack[1] = &PlayerRunSet;
	PlayerIndex[0] = IDLE;
	PlayerIndex[1] = RUN;
	animPack PlayerPack = animPack(Player_AnimCount,PlayerAnimPack,PlayerIndex);
	//

	TTF_Font* arial = TTF_OpenFont("C:\\Users\\baptistac1\\Documents\\Visual Studio 2013\\Projects\\LearnEngine\\LearnEngine\\fonts\\ARIAL.TTF", 12);

	SDL_Surface* surface = LoadSurfaceBMP("FloatingDirtLand.bmp");

	SDL_Texture* Back = SDL_CreateTextureFromSurface(ren, surface);


	int w;
	int h;
	SDL_QueryTexture(Back, NULL, NULL, &w, &h);


	Terrain ter = Terrain(surface);

	Actor bandanaman         = Actor(ren, &ter, NULLPack, "RedBox.bmp", 290, 160, 740, 640);
	Actor bandanamanplus	 = Actor(ren, &ter, NULLPack, "RedBox.bmp", 290, 160, 460, 640);
	Actor minibandanamanplus = Actor(ren, &ter, PlayerPack, "RedBox.bmp", 30, 30, 460, 675);
	Actor bandanawoman		 = Actor(ren, &ter, NULLPack, "RedBox.bmp", 290, 160, 300, 640);
	Actor redbox1			 = Actor(ren, &ter, NULLPack, "RedBoxWithTrans.bmp", 200, 200, 0, 0);
	Actor bluebox1			 = Actor(ren, &ter, NULLPack, "BlueBox.bmp", 200, 200, 100, 400);
	Actor lilred		 	 = Actor(ren, &ter, NULLPack, "lilred.bmp", 1, 1, 1, 1); //It's lil' red, the debug pixel!

	//Actor Cast[100];
	//for (int i = 0; i < 100; i++)
	//{
	//	Cast[i] = Actor(ren, "RedBox.bmp", 290, 160, i*70, 340);
	//}

	SDL_Rect wrldrect;
	wrldrect.w = (int)(((float)SCREEN_W));
	wrldrect.h = (int)(((float)SCREEN_H));
	wrldrect.x = 0;
	wrldrect.y = 0;

	int cycle = 0;

	SDL_Event e;

	bool quit = false;
	bool forward = true;
	while (!quit)
	{
		int CycleStart = GetTimeMS();
		//gCons->ConsPrintf("HELLO WORLD! %i\n", cycle);
		//gCons->ConsPrintf("Blu pos: x = %i, y = %i\n", bluebox1.GetX(), bluebox1.GetY());
		//gCons->ConsPrintf("Red Wrld pos: x = %i, y = %i\n", redbox1.GetX(), redbox1.GetY());
		//gCons->ConsPrintf("Red Wrld pos: x = %i, y = %i\n", lilred.GetX(), lilred.GetY());

		//gCons->ConsPrintf("time(ms) = %i \n", GetTimeMS());

		SDL_RenderClear(ren);
		SDL_RenderCopy(ren, Back, cam.GetCamView(), NULL);

		//cam.SetCameraPos(ren, (redbox1.GetX()-0), redbox1.GetY()-0);
		//cam.ArrowKeyMove(ren, 10, 10, &e);
		minibandanamanplus.ControlActor(6, 6, &e);
		minibandanamanplus.ActorUpdate();
		cam.ActorFollow(ren, minibandanamanplus, 200 , 150);

		DrawActorTex(ren, bluebox1, cam);
		//SDL_Rect ScrPos = DrawActorTex(ren, redbox1, cam);
		//SDL_Rect ScrPos = DrawActorTex(ren, lilred, cam);
		//gCons->ConsPrintf("Red Scrn Pos: x = %i, y = %i\n", ScrPos.x, ScrPos.y);
		//rCons->ConsPrintf("Red Scrn Pos: x = %i, y = %i\n", ScrPos.x, ScrPos.y);

//		DrawActorAnim(ren, bandanaman, &RunMan, cam, SDL_FLIP_NONE);
//		DrawActorAnim(ren, bandanawoman, &RunWoman, cam, SDL_FLIP_NONE);
//		DrawActorAnim(ren, bandanamanplus, &RunManPlus, cam, SDL_FLIP_NONE);

		//DrawActorTex(ren, minibandanamanplus, cam);
		DrawActor(ren, minibandanamanplus, cam);
		DrawRect(ren, ter.LowerBounder, cam);
		DrawRect(ren, ter.UpperBounder, cam);
		DrawRect(ren, ter.LeftBounder, cam);
		DrawRect(ren, ter.RightBounder, cam);
		//DrawActorAnim(ren, minibandanamanplus, &PlayerTempIdleTest, cam, minibandanamanplus.GetDir());

		ter.DetectGroundIntersect(&minibandanamanplus.GetRect());

		rCons->DrawConsoleReadout(ren, 400, 0);
		gCons->DrawConsole(ren);
		

		SDL_RenderPresent(ren);
		
		if ((redbox1.GetX() + (redbox1.GetWidth())) > WORLD_W)
		{
			forward = false;
		}
		if (redbox1.GetX() < 0)
		{
			forward = true;
		}

		if (forward == true)
		{
			//redbox1.MoveActorCollision(5, 2);
			//bluebox1.MoveActorCollision(5, -2);
		}
		else
		{
			//redbox1.MoveActorCollision(-5, -2);
			//bluebox1.MoveActorCollision(-5, 2);
		}

		SDL_PollEvent(&e);

		if (e.type == SDL_QUIT)
		{
			quit = true;
		}
		cycle = cycle + 1;
		
		int DeltaTime = (GetTimeMS() - CycleStart);
		assert(DeltaTime >= 0);

		int DelayTime = MS_PER_FRAME - DeltaTime;

		if (DelayTime >= 0)
		{
			//gCons->ConsPrintf("Delay Time: %i \n", DelayTime);
			SDL_Delay(DelayTime);
		}
		else
		{
			//gCons->ConsPrintf("Delay Time: %i FRAME DROP\n", DelayTime);
		}
	}

	delete gCons;
	SDL_FreeSurface(surface);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}