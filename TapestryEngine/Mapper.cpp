#include "Mapper.h"

//Feature Functions
SDL_Rect* Feature::GenerateRoom(int h_max, int h_min, int w_max, int w_min)
{
	mPositon = new SDL_Rect;
	mPositon->h = gRandom->RandRange(h_min, h_max);
	mPositon->w = gRandom->RandRange(w_min, w_max);
	mPositon->x = -1;
	mPositon->y = -1;

	return mPositon;
}
//

//Mapper Functions

bool Mapper::FillRegion(int ttype, SDL_Rect* bounds)
{
	Uint8* map = (Uint8*)mMap->pixels;

	if (bounds == NULL) //fill the entire map, used during initial map creation
	{
		memset(map, ttype, (mMap->w*mMap->h));
		return true;
	}


	if ((bounds->x == -1) | (bounds->y == -1)) //error case
	{
		gCons->ConsPrintf("feature XY not initialized\n");
		return false;
	}


	else
	{
		if (bounds->y < 0)
		{
			bounds->y = 0;
		}
		if (bounds->y >(mMap->h - bounds->h))
		{
			bounds->y = (mMap->h - bounds->h);
		}
		for (int y = bounds->y; y < (bounds->y + bounds->h); y++)
		{
			if (bounds->x < 0)
			{
				bounds->x = 0;
			}
			if (bounds->x >(mMap->pitch - bounds->w))
			{
				bounds->x = (mMap->pitch - bounds->w);
			}
			for (int x = bounds->x; x < (bounds->x + bounds->w); x++)
			{
				map[(y*mMap->pitch) + x] = ttype;
			}
		}
	}
	return true;
}

void Mapper::BuildFeature(Feature* fea)
{
	FillRegion(AIR, fea->GetPosition());
}

bool Mapper::AttachFeature(Feature* stem, Feature* bud)
{
	SDL_Rect* stem_pos = stem->GetPosition();
	SDL_Rect* bud_pos  = bud->GetPosition();

	int face = gRandom->RandRange(1, 4);
	gCons->ConsPrintf("%i\n", face);
//	assert(face <= 2);
//	assert(face >= 1);
	switch (face)
	{
	case 1: //attach left
		bud_pos->x = (stem_pos->x - bud_pos->w);
		bud_pos->y = gRandom->RandRange(stem_pos->y, ((stem_pos->y + stem_pos->h) - bud_pos->h));
		//bud->SetRotate(false);
		return true;
		break;
	case 2: //attach right
		bud_pos->x = (stem_pos->x + stem_pos->w);
		bud_pos->y = gRandom->RandRange(stem_pos->y, ((stem_pos->y + stem_pos->h) - bud_pos->h));
		//bud->SetRotate(false);
		return true;
		break;
	case 3: //attach top
		bud_pos->x = gRandom->RandRange(stem_pos->x, ((stem_pos->x + stem_pos->w) - bud_pos->w));
		bud_pos->y = (stem_pos->y - bud_pos->h);
		//bud->SetRotate(true);
		return true;
		break;
	case 4: //attach bottom
		bud_pos->x = gRandom->RandRange(stem_pos->x, ((stem_pos->x + stem_pos->w) - bud_pos->w));
		bud_pos->y = (stem_pos->y + stem_pos->h);
		//bud->SetRotate(true);
		return true;
		break;
	default:
		return false;
		break;
	}
}


bool Mapper::FitFeature(Feature* stem, Feature* bud, int attempts)
{
	if (attempts >= MAX_ATTEMPTS)
	{
		return false;
	}
	attempts++;

	if (stem == NULL) //no feature to attach to
	{
		SDL_Rect* f_pos = bud->GetPosition();
		int x = gRandom->RandRange(0, (mMap->w - f_pos->w));
		int y = gRandom->RandRange(0, (mMap->h - f_pos->h));
		bud->SetXY(x, y);
	}
	else
	{
		AttachFeature(stem, bud);
	}

	for (int i = 0; i < mFeatureIndex; i++)
	{
		if (mFeature_Array[i] != stem)
		{
			if (DetectRectIntersect(bud->GetPosition(), mFeature_Array[i]->GetPosition()) == true)
			{
				return FitFeature(stem, bud, attempts); //featue did not fit try again
			}
		}
	}
	return true; //feature successfully fitted
}

Feature* Mapper::SelectFeature(FeatureType ft)
{
	switch (ft)
	{
	case ROOM_TEST:
		return new Room_test();
		break;
	case HALL_TEST:
		return new Hall_test();
		break;
	default:
		return NULL;
		break;
	}
}


void Mapper::AddFeature()
{
	Feature* bud  = NULL;
	Feature* stem = NULL;
	
	if (mFeatureIndex != 0)
	{
		int start_index = gRandom->RandRange(0, mFeatureIndex - 1);
		stem = mFeature_Array[start_index];

		int* table = stem->GetConnectableFeatures();
		int roll = gRandom->RandRange(0, 100);
		
		int counter = table[0];
		for (int i = 0 ; i < sizeof(table); i++)
		{
			if (roll <= counter)
			{
				bud = SelectFeature((FeatureType)i);
				break;
			}
			else
			{
				counter += table[i + 1];
			}
		}

	}
	else //mFeatureIndex == 0 ie this is the first feature
	{
		bud = new Room_test();
		FitFeature(NULL, bud);
		mFeature_Array[mFeatureIndex] = bud;
		mFeatureIndex++;
		BuildFeature(bud);
		return;
	}
	
	//Feature* fea = new Feature(100, 30, 200, 60);
	if (FitFeature(stem, bud) == true)
	{
		mFeature_Array[mFeatureIndex] = bud;
		mFeatureIndex++;
		BuildFeature(bud);
	}
}

SDL_Surface* Mapper::NewMap(int h, int w)
{
	//SDL_Surface* Map = SDL_CreateRGBSurface(0, w, h, 32, rmask, gmask, bmask, amask);
	mMap = SDL_CreateRGBSurface(0, w, h, 8, 0, 0, 0, 0);

	if (mMap == NULL)
	{
		const char* error = SDL_GetError();
		//SDL_Log("SDL_CreateRGBSurface() failed: %s", SDL_GetError());
		exit(1);
	}

	if (mMap->format->format != SDL_PIXELFORMAT_INDEX8)
	{
		gCons->ConsPrintf("Non-INDEX8 Collision Map Detected\n");
		return NULL;
	}
	Uint8* PixMap = (Uint8*)mMap->pixels;

	FillRegion(GROUND);

	for (int i = 0; i < 3; i++)
	{
		//AddFeature();
	}
	
	SDL_Color air = { 255, 255, 255 };
	SDL_Color ground = { 0, 0, 0 };
	SDL_Color platform = { 220, 220, 220 };
	SDL_Color water = { 0, 0, 255 };

	SDL_Color colors[4] = { air, ground, platform, water };

	SDL_SetPaletteColors(mMap->format->palette, colors, 0, 3);
	return mMap;
}

SDL_Surface* Mapper::GenerateMap(int h, int w)
{
	return NewMap(h, w);
}
