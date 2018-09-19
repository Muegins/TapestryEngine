#include "Utils.h"
#include "DiagnosticDraw.h"
#include "Console.h"

ParticleTypeData NullPTdata()
{
	ParticleTypeData ptData;
	ptData.NoData = true;
	return ptData;
}

Time* gTime = NULL;
Random* gRandom = NULL;

//int GetTimeF() //measures in frames
//{
//	int time = (clock() / CLOCKS_PER_FRAME);
//	return time;
//}

int GetRealTimeMS() //measures in milliseconds
{
	int time = (clock() / (CLOCKS_PER_SEC / 1000));
	return time;
}

SDL_Surface* LoadSurfaceBMP(const char* filename)
{
#ifdef DEBUG
	char* basepath = "C:\\Users\\baptistac1\\Documents\\Visual Studio 2015\\Projects\\TapestryEngineDev\\TapestryEngine\\imgs\\";
#endif

#ifdef RELEASE
	char* basepath = ".\\imgs\\";
#endif

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

TTF_Font* LoadFont(char* filename, int ptsize)
{
#ifdef DEBUG
	char* basepath = "C:\\Users\\baptistac1\\Documents\\Visual Studio 2015\\Projects\\TapestryEngineDev\\TapestryEngine\\fonts\\";
#endif

#ifdef RELEASE
	char* basepath = ".\\fonts\\";
#endif

	char pathbuffer[1024];
	strcpy(pathbuffer, basepath);
	char* fullpath = strcat(pathbuffer, filename);

	TTF_Font* font = TTF_OpenFont(fullpath, ptsize);

	const char* error = TTF_GetError();

//	int msgboxID = MessageBox(
//		NULL,
//		(LPCSTR)error,
//		(LPCSTR)L"Account Details",
//		MB_ICONWARNING | MB_CANCELTRYCONTINUE | MB_DEFBUTTON2
//	);

	assert(font != NULL);
	
	//gCons->ConsPrintf(fullpath);

	return font;
}
cJSON * LoadJSON(const char* filename)
{
#ifdef DEBUG
	char* basepath = "C:\\Users\\baptistac1\\Documents\\Visual Studio 2015\\Projects\\TapestryEngineDev\\TapestryEngine\\json\\";
#endif

#ifdef RELEASE
	char* basepath = ".\\json\\";
#endif

	char pathbuffer[1024];
	strcpy(pathbuffer, basepath);
	strcat(pathbuffer, filename);

	struct stat filestats;
	stat(pathbuffer, &filestats);

	char* filecontent = (char*)malloc( (filestats.st_size + 1) );

	FILE* fp;
	fp = fopen(pathbuffer, "rt");
	
	size_t size = fread(filecontent, 1, filestats.st_size, fp);
	fclose(fp);

	filecontent[size] = 0;

	//gCons->ConsPrintf("%s\n", filecontent);

	return cJSON_Parse(filecontent);
}

void PrintJSON(cJSON* json)
{
	gCons->ConsPrintf(cJSON_Print(json));
}

float GetSign(float x)
{
	if (x > 0) { return  1; }
	if (x < 0) { return -1; }
	return 0;
}

bool DetectRectIntersect(SDL_Rect* r1, SDL_Rect* r2)
{
	//if ( ((r1->x <= r2->x) && (r2->x <= (r1->x + r1->w))) || ( (r1->x <= (r2->x + r2->w)) && ((r2->x + r2->w) <= (r1->x + r1->w)) )) //if r1 and r2 intersect in x

	int r1x1 = r1->x;
	int r1x2 = r1->x + r1->w;
	int r2x1 = r2->x;
	int r2x2 = r2->x + r2->w;

	int r1y1 = r1->y;
	int r1y2 = r1->y + r1->h;
	int r2y1 = r2->y;
	int r2y2 = r2->y + r2->h;

	//if (((r1->x <= r2->x) && (r2->x <= (r1->x + r1->w))) || ((r1->x <= (r2->x + r2->w)) && ((r2->x + r2->w) <= (r1->x + r1->w))) || ((r1->x <= r2->x) && (r2->x + r2->w) >= (r1->x + r1->w)) || ( (r1->x >= r2->x)&&( (r1->x + r1->w) >= (r2->x + r2->w) ) ) ) //if r1 and r2 intersect in x
	if
	(
	(r1x1 <= r2x2 && r1x1 >= r2x1) ||
	(r1x2 <= r2x2 && r1x2 >= r2x1) ||
	(r1x1 <= r2x1 && r1x2 >= r2x2)
	)
	{
		if
		(
		(r1y1 <= r2y2 && r1y1 >= r2y1) ||
		(r1y2 <= r2y2 && r1y2 >= r2y1) ||
		(r1y1 <= r2y1 && r1y2 >= r2y2)
		)
		{
			//gCons->ConsPrintf("Rect Intersect Detected!\n");
			return true;
		}
	}
	//gCons->ConsPrintf("No Rect Intersect Detected!\n");
	return false;
}

bool DetectCenterPointIntersect(SDL_Rect* zone, SDL_Rect* point)
{
	//gDiagDraw->LogDiagRect(*point);
	int pointX = point->x + (int)((float)point->w / 2);
	int pointY = point->y + (int)((float)point->h / 2);
	if ( (zone->x <= pointX) && (pointX <= (zone->x + zone->w)) )
	{
		if ((zone->y <= pointY) && (pointY <= (zone->y + zone->h)))
		{
			//gCons->ConsPrintf("Center point intersect detected\n");
			return true;
		}
	}
	//gCons->ConsPrintf("center point not intersecting\n");
	return false;
}

int CalcDistance(int x1, int y1, int x2, int y2)
{
	int Xdelt = abs(x1 - x2);
	int Ydelt = abs(y1 - y2);

	return (int)sqrt((Xdelt*Xdelt) + (Ydelt*Ydelt));
}

int EvenOutcomes(int NumberofOutcomes)
{
	int	i = (rand() % (NumberofOutcomes)) + 1;
	//gCons->ConsPrintf("Roll : %i\n", i);
	return i;
}

Random::Random()
{
	mSeed = (int)time(NULL);
	srand(mSeed);
}

int Random::RandRange(int v1, int v2)
{
	int i;
	if (v1 < v2) //v1 is min
	{
		i = (v1 + (rand() % (1 + v2 - v1)) );
		assert(i <= v2);
		assert(i >= v1);
	}
	else if (v2 < v1) //v2 is min
	{
		i = (v2 + (rand() % (1 + v1 - v2)) );
		assert(i <= v1);
		assert(i >= v2);
	}
	else// v1 == v2
	{
		i = v1;
	}
	//gCons->ConsPrintf("Range Roll : %i\n", i);
	return i;
}


bool IsEven(int i) //Not working alawys return true
{
	if ( (i % 2) == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}