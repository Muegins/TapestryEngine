#ifndef MISCDRAW_H
#define MISCDRAW_H

#include"Actor.h"
#include"bones.h"
#include"Camera.h"
#include"Utils.h"

SDL_Rect GetScreenPos(Actor& act, Camera cam);

SDL_Rect DrawActorAnim(SDL_Renderer* ren, Actor& act, animation* anim, Camera cam, int dir);

bool DrawParallax(SDL_Renderer* ren, SDL_Texture* img, Camera cam, float scale, int worldH, int worldW);

SDL_Rect DrawActor(SDL_Renderer* ren, Actor& act, Camera cam);

bool DrawRect(SDL_Renderer* mRen, SDL_Rect WrldPos, Camera& mCam);

bool DrawText(SDL_Renderer* ren, char* text);

bool DrawBone(SDL_Renderer* ren, Bone* bone);

bool DrawMapTest(SDL_Renderer* ren, SDL_Surface* map);
#endif