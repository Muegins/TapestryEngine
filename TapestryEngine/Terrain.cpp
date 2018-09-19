#include "Terrain.h"
#include "DiagnosticDraw.h"


TerrainCollisionManager::TerrainCollisionManager(SDL_Surface* Col_Map)
{
	mCol_Map = Col_Map;	
}

bool TerrainCollisionManager::DetectTerrainIntersect(SDL_Rect* Bounds, int ttype1, int ttype2)
{
	if (mCol_Map->format->format != SDL_PIXELFORMAT_INDEX8)
	{
		gCons->ConsPrintf("Non-INDEX8 Collision Map Detected\n");
		return false;
	}
	Uint8* PixMap = (Uint8*)mCol_Map->pixels;
	if (Bounds->y < 0)
	{
		Bounds->y = 0;
	}
	if (Bounds->y > (mCol_Map->h - Bounds->h))
	{
		Bounds->y = (mCol_Map->h - Bounds->h);
	}
	for (int y = Bounds->y; y < (Bounds->y + Bounds->h); y++)
	{
		if (Bounds->x < 0)
		{
			Bounds->x = 0;
		}
		if (Bounds->x > (mCol_Map->pitch - Bounds->w))
		{
			Bounds->x = (mCol_Map->pitch - Bounds->w);
		}

		if (ttype2 == -1)
		{
			for (int x = Bounds->x; x < (Bounds->x + Bounds->w); x++)
			{
				if (PixMap[(y*mCol_Map->pitch) + x] == ttype1)
				{
					//gCons->ConsPrintf("ground collision detected \n");
					//gDiagDraw->LogPixel(x, y);
					return true;
				}
				else
				{
					//gCons->ConsPrintf("no collision detected \n");
				}
			}
		}
		else
		{
			for (int x = Bounds->x; x < (Bounds->x + Bounds->w); x++)
			{
				if ( (PixMap[(y*mCol_Map->pitch) + x] == ttype1) || (PixMap[(y*mCol_Map->pitch) + x] == ttype2) )
				{
					//gCons->ConsPrintf("ground collision detected \n");
					//gDiagDraw->LogPixel(x, y);
					return true;
				}
			}
		}

	}
	return false;
}

bool TerrainCollisionManager::DetectWorldEscape(SDL_Rect* Bounds)
{
	//if(Bounds->x)
	return false;
}

void TerrainCollisionManager::DrawTerrain()
{
	SDL_Rect bds;
	SDL_Rect* Bounds = &bds;
	Bounds->x = 0;
	Bounds->y = 0;
	Bounds->h = mCol_Map->h;
	Bounds->w = mCol_Map->w;
	
	if (mCol_Map->format->format != SDL_PIXELFORMAT_INDEX8)
	{
		gCons->ConsPrintf("Non-INDEX8 Collision Map Detected\n");
	}
	Uint8* PixMap = (Uint8*)mCol_Map->pixels;
	if (Bounds->y < 0)
	{
		Bounds->y = 0;
	}
	if (Bounds->y >(mCol_Map->h - Bounds->h))
	{
		Bounds->y = (mCol_Map->h - Bounds->h);
	}
	for (int y = Bounds->y; y < (Bounds->y + Bounds->h); y++)
	{
		if (Bounds->x < 0)
		{
			Bounds->x = 0;
		}
		if (Bounds->x >(mCol_Map->pitch - Bounds->w))
		{
			Bounds->x = (mCol_Map->pitch - Bounds->w);
		}

			for (int x = Bounds->x; x < (Bounds->x + Bounds->w); x++)
			{
				if ((PixMap[(y*mCol_Map->pitch) + x] == GROUND) || (PixMap[(y*mCol_Map->pitch) + x] == PLATFORM))
				{
					//gCons->ConsPrintf("ground collision detected \n");
					gDiagDraw->LogPixel(x, y);
				}
			}
	}
}

//colman_Character functions
colman_Character::colman_Character(SDL_Surface* Col_Map, SDL_Rect* PosData, SDL_Rect* DestData, int EdgeThickness) : TerrainCollisionManager(Col_Map)
{
	mPlatformCollision = true;

	mWallThickness = EdgeThickness;
	
	mPosition = PosData;
	mDestination = DestData;
}

bool colman_Character::DetectEdgeCollision(SDL_Rect* Bounds)
{
	SDL_Rect LowerBounder;
	LowerBounder.h = mWallThickness;
	LowerBounder.w = Bounds->w;
	LowerBounder.x = Bounds->x;
	LowerBounder.y = ((Bounds->y + Bounds->h) - LowerBounder.h);

	SDL_Rect UpperBounder;
	UpperBounder.h = mWallThickness;
	UpperBounder.w = Bounds->w;
	UpperBounder.x = Bounds->x;
	UpperBounder.y = Bounds->y;

	SDL_Rect RightBounder;
	RightBounder.w = mWallThickness;
	RightBounder.x = ((Bounds->x + Bounds->w) - RightBounder.w);
	RightBounder.h = Bounds->h;
	RightBounder.y = Bounds->y;

	SDL_Rect LeftBounder;
	LeftBounder.w = mWallThickness;
	LeftBounder.x  = Bounds->x;
	LeftBounder.h  = Bounds->h;
	LeftBounder.y  = Bounds->y;


	if (mPlatformCollision == true)
	{		
		if ((DetectTerrainIntersect(&LowerBounder, GROUND, PLATFORM) == true) ||
			(DetectTerrainIntersect(&UpperBounder, GROUND          ) == true) ||
			(DetectTerrainIntersect(&RightBounder, GROUND          ) == true) ||
			(DetectTerrainIntersect(&LeftBounder , GROUND          ) == true))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else //PlatformCollision if false
	{
		if ((DetectTerrainIntersect(&LowerBounder, GROUND) == true) ||
			(DetectTerrainIntersect(&UpperBounder, GROUND) == true) ||
			(DetectTerrainIntersect(&RightBounder, GROUND) == true) ||
			(DetectTerrainIntersect(&LeftBounder , GROUND) == true))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

int colman_Character::DetectIncline(int StepSizeLimit) //StepSizeLimit is the smallest step that CANNOT be climbed
{
	SDL_Rect Scanner = *mDestination;
	Scanner.h = 1;

	if (mPlatformCollision == true)
	{
		for (int i = 0; i < StepSizeLimit; i++)
		{
			Scanner.y = ((mDestination->y + mDestination->h) - StepSizeLimit) + i;
			if (DetectTerrainIntersect(&Scanner, GROUND, PLATFORM) == true)
			{
				//gCons->ConsPrintf("Step is %i Pixels tall \n", (StepSizeLimit - i) );
				return (StepSizeLimit - i);
			}
		}
	}
	else
	{
		for (int i = 0; i < StepSizeLimit; i++)
		{
			Scanner.y = ((mDestination->y + mDestination->h) - StepSizeLimit) + i;
			if (DetectTerrainIntersect(&Scanner, GROUND) == true)
			{
				//gCons->ConsPrintf("Step is %i Pixels tall \n", (StepSizeLimit - i) );
				return (StepSizeLimit - i);
			}
		}
	}
	return StepSizeLimit;
}

bool colman_Character::DetectFalling()
{
	SDL_Rect GroundDetector = *mPosition;
	GroundDetector.y = (mPosition->y + mPosition->h);
	GroundDetector.h = 1;

	return !( DetectTerrainIntersect(&GroundDetector, GROUND, PLATFORM));
}

bool colman_Character::DetectDirectionalCollision(SDL_Rect* bounds, int dir)
{
	SDL_Rect bumper = *bounds;
	switch (dir)
	{
	case LEFT:
		bumper.x -= 1;
		bumper.w = 1;
		bumper.h -= 4;
		break;
	case RIGHT:
		bumper.x += bumper.w;
		bumper.w = 1;
		bumper.h -= 4;
		break;
	case UP:
		bumper.h = 1;
		break;
	case DOWN:
		bumper.y += bumper.h;
		bumper.h = 1;
		break;
	}

	if ((mPlatformCollision == true) && (dir == DOWN))
	{
		if (DetectTerrainIntersect(&bumper, GROUND, PLATFORM))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else //PlatformCollision if false
	{
		if (DetectTerrainIntersect(&bumper, GROUND))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

bool colman_Character::DetectSideCollision(SDL_Rect* Bounds)
{
	
	SDL_Rect RightDetector;
	RightDetector.w = 1;
	RightDetector.y = Bounds->y;
	RightDetector.x = (Bounds->x + Bounds->w);
	RightDetector.h = Bounds->h - 1;
	
	SDL_Rect LeftDetector;
	LeftDetector.w = 1;
	LeftDetector.y = Bounds->y;
	LeftDetector.x = (Bounds->x - 1);
	LeftDetector.h = Bounds->h - 1;
	
	return (DetectTerrainIntersect(&LeftDetector, GROUND) | DetectTerrainIntersect(&RightDetector, GROUND));
}

bool colman_Character::DetectSwim()
{	
	SDL_Rect Under;
	Under.h = 1;
	Under.w = mPosition->w;
	Under.x = mPosition->x;
	Under.y = (mPosition->y + 6);//6 shouldn't hardcoded

	return DetectTerrainIntersect(&Under, WATER);
}

bool colman_Character::DetectSurface()
{
	SDL_Rect Under;
	Under.h = 1;
	Under.w = mPosition->w;
	Under.x = mPosition->x;
	Under.y = (mPosition->y + 6);//6 shouldn't hardcoded

	SDL_Rect Over = Under;
	Over.y -= 1;

	//gDiagDraw->LogDiagRect(Over);
	//gDiagDraw->LogDiagRect(Under);

	if ((DetectTerrainIntersect(&Under, WATER) == true) && (DetectTerrainIntersect(&Over, AIR) == true))
	{
		//gCons->ConsPrintf("surface detected\n");
		return true;
	}
	else
	{
		return false;
	}
}

int colman_Character::FindSurface()
{
	SDL_Rect surface_scan = *mPosition;
	surface_scan.w = 1;
	surface_scan.h = 1;
	for (int y = 0; y < mPosition->h; y++)
	{
		surface_scan.y += y;
		if (DetectTerrainIntersect(&surface_scan, WATER))
		{
			return surface_scan.y - 1;
			gCons->ConsPrintf("Surface Found at y = %i", surface_scan.y);
		}
	}
	return -1;
}

bool colman_Character::DetectWade()
{
	SDL_Rect LowerBounder = *mPosition;
	LowerBounder.h = mWallThickness;
	LowerBounder.y = ((mPosition->y + mPosition->h) - LowerBounder.h);

	return DetectTerrainIntersect(&LowerBounder, WATER);
}
