#ifndef MAPPER_H
#define MAPPER_H

#include "Utils.h"
#include "Console.h"

#define MAX_FEATURES 100
#define MAX_ATTEMPTS 10

//#if SDL_BYTEORDER == SDL_BIG_ENDIAN
//Uint32 rmask = 0xff000000;
//Uint32 gmask = 0x00ff0000;
//Uint32 bmask = 0x0000ff00;
//Uint32 amask = 0x000000ff;
//#else
//Uint32 rmask = 0x000000ff;
//Uint32 gmask = 0x0000ff00;
//Uint32 bmask = 0x00ff0000;
//Uint32 amask = 0xff000000;
//#endif

enum FeatureType
{
	ROOM_TEST,
	HALL_TEST
};

class Feature
{
public:

	Feature() {};

	Feature(int h_max, int h_min, int w_max, int w_min)
	{
		GenerateRoom(h_max, h_min, w_max, w_min);
	}

	SDL_Rect* GetPosition()
	{
		return mPositon;
	}

	bool GetRotate()
	{
		return mRotated;
	}

	void SetXY(int x, int y)
	{
		mPositon->x = x;
		mPositon->y = y;
	}

	void SetRotate(bool rot)
	{
		mRotated = rot;
	}

	SDL_Rect* GenerateRoom(int h_max, int h_min, int w_max, int w_min);

	int* GetConnectableFeatures()
	{
		return mConnectableFeatures;
	}


protected:

	SDL_Rect* mPositon;
	bool mRotated;

	int mConnectableFeatures[2];
};

class Room_test : public Feature
{
public:

	Room_test() : Feature(100, 30, 200, 60)
	{
		mConnectableFeatures[ROOM_TEST] = 0;
		mConnectableFeatures[HALL_TEST] = 100;
	}

protected:


};

class Hall_test : public Feature
{
public:

	Hall_test() : Feature(10, 10, 100, 10)
	{
		mConnectableFeatures[ROOM_TEST] = 0;
		mConnectableFeatures[HALL_TEST] = 100;
	}

protected:

};

class Mapper
{
public:

	Mapper() : mFeatureIndex(0) {}

	SDL_Surface* GetMap()
	{
		return mMap;
	}

	bool FillRegion(int ttype, SDL_Rect* bounds = NULL);

	void BuildFeature(Feature* fea);

	bool AttachFeature(Feature* stem, Feature* bud);

	bool FitFeature(Feature* stem, Feature* bud, int attempts = 0);

	Feature* SelectFeature(FeatureType ft);

	void AddFeature();

	SDL_Surface* NewMap(int h, int w);

	SDL_Surface* GenerateMap(int h, int w);
protected:

	SDL_Surface* mMap;
	Feature* mFeature_Array[MAX_FEATURES];
	int mFeatureIndex;
};

#endif
