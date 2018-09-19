#ifndef TERRAIN_H
#define TERRAIN_H

#include "Utils.h"
#include "Console.h"

//now defined in utils.h
//#define AIR			0x00
//#define GROUND		0x01
//#define PLATFORM	0x02
//#define WATER		0x03

//BUG: Diagonal Stretch occurs when world H and world W are not multiples

class TerrainCollisionManager
{
public:

	TerrainCollisionManager() : mCol_Map(NULL) {}

	TerrainCollisionManager(SDL_Surface* Col_Map);

	bool DetectTerrainIntersect(SDL_Rect* Bounds, int ttype1, int ttype2 = -1);

	bool DetectWorldEscape(SDL_Rect* Bounds);
	
	void DrawTerrain(); //scans the entire collison map and draws each pixel, utterly obliterates framerate

protected:
	SDL_Surface* mCol_Map;
};

class colman_Character : public TerrainCollisionManager
{
public:

	colman_Character() {}

	colman_Character(SDL_Surface* Col_Map, SDL_Rect* PosData, SDL_Rect* DestData, int EdgeThickness);

	bool DetectEdgeCollision(SDL_Rect* Bounds);

	int DetectIncline(int StepSizeLimit);

	bool DetectFalling();

	bool DetectDirectionalCollision(SDL_Rect* bounds, int dir);

	bool DetectSideCollision(SDL_Rect* Bounds);

	bool DetectSwim();

	bool DetectSurface();

	int FindSurface();

	bool DetectWade();

	bool SetPlaformCollision(bool b)
	{
		//gCons->ConsPrintf("Platform Collisions %i\n", b);
		return mPlatformCollision = b;
	}

protected:

	bool mPlatformCollision;

	SDL_Rect* mPosition;
	SDL_Rect* mDestination;

	int mWallThickness;

};

#endif
