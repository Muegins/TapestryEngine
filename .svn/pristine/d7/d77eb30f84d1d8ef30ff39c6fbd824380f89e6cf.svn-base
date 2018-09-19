#include "Loading.h"

bool Loading::Load(const char* filename)
{

	cJSON* root = LoadJSON(filename);
	//PrintJSON(root);
	cJSON* loading = cJSON_GetObjectItem(root, "loading");

	char* SplashPath = cJSON_GetObjectItem(loading, "splash")->valuestring;
	
	mSplash = SDL_CreateTextureFromSurface(mRen, LoadSurfaceBMP(SplashPath));
	return true;
}

bool Loading::Update()
{
	SDL_RenderCopy(mRen, mSplash , NULL, NULL);
	
	return true;
}
