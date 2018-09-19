#include "Utils.h"
#include "Console.h"
#include "MiscDraw.h"
#include "DiagnosticDraw.h"
#include "ActorCollision.h"
#include "Input.h"
#include "Actor.h"
#include "sound.h"

#include "Dialogue.h"

#include "Loading.h"
#include "Level.h"

#include "BinaryTree.h" //remove later

FILE _iob[] = { *stdin, *stdout, *stderr };

extern "C" FILE * __cdecl __iob_func(void)
{
	return _iob;
}

int main(int argc, char *argv[])
{
	gTime = new Time();
	gRandom = new Random();

	TTF_Init();
//	BinaryTree TestTree = BinaryTree(new Node(10, NULL));
//	TestTree.Insert(5, NULL);
//	TestTree.Insert(15, NULL);
//	TestTree.Insert(7, NULL);
//	TestTree.Insert(2, NULL);
//	TestTree.Insert(20, NULL);
//	TestTree.Insert(17, NULL);
//	TestTree.Insert(35, NULL);
//	TestTree.Insert(31, NULL);
//	int s = TestTree.Size();

//	Node** contents = TestTree.Dump();

	//Node* tar = TestTree.Search(5);//->Delete();

	//char buff1[256];
	//memset(buff1, 0, sizeof(buff1));
	//ReadBTree(&TestTree, buff1);
	//tar->Delete();
	//char buff2[256];
	//memset(buff2, 0, sizeof(buff2));
	//ReadBTree(&TestTree, buff2);

//	Node* Tree = new Node();
//	Tree->InsertNode()

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_AUDIO) != 0)
	{
		gCons->ConsPrintf("SDL_Init Error: %s\n", SDL_GetError());
		SDL_Quit();
		return 1;
	}

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
//	Mix_Init(MIX_INIT_MP3);

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

	SDL_Renderer* ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren == NULL)
	{
		gCons->ConsPrintf("SDL_CreateRenderer Error: %s", SDL_GetError());
		SDL_Quit();
		return 1;
	}

#ifdef DEBUG
	SDL_Color fg = { 255, 255, 255 };
	SDL_Color bg = { 0, 0, 255 };
	gCons = new Console("ARIAL.TTF", 12, fg, bg);
	//gCons = new Console("Tapestry.ttf", 16, fg, bg);
#endif // DEBUG


	Control ctrl = Control();

	ContextManager ConMan = ContextManager("level_arid_land.json");

	Level* lvl = new Level(ren, &ctrl);
	ConMan.LogContext(lvl, "level");
	//DiagnosticDraw* gDiagDraw = new DiagnosticDraw(ren, lvl->mCam);

	Loading* load = new Loading(ren);
	ConMan.LogContext(load, "load");

//------------Mapper Test-----------------------	
//	MapTest* map_test = new MapTest(ren);
//	ConMan.LogContext(map_test, "map_test");

//	ConMan.LoadContext("map_test");
//	ConMan.ContextUpdate();
//	SDL_RenderPresent(ren);
//-----------------------------------------------

	ConMan.LoadContext("load");
	ConMan.ContextUpdate();
	SDL_RenderPresent(ren);

	ConMan.LoadContext("level");

	//Mix_Chunk* dhaka = LoadSound("Dhaka.mp3");
	//Mix_Chunk* ftst = LoadSound("footstep.wav");

	SDL_Event e;

	//if (Mix_PlayingMusic() == false)
	//{
		//Mix_PlayMusic(dhaka, -1);
		//Mix_Volume(1, 6);
		//Mix_VolumeChunk(dhaka, 6);
		//Mix_PlayChannel(1, dhaka, -1);

	//}
	bool quit = false;
	while (!quit)
	{
		int CycleStart = GetRealTimeMS();
		//srand(time(NULL));

		SDL_RenderClear(ren);

		ctrl.ProcessKeyboard();

		ConMan.ContextUpdate();

		//PrintBTree(&TestTree);

#ifdef DEBUG
		gCons->DrawConsole(ren); //Console is currently causing crashes for unknown reasons. No changes made to console system; very confusing
#endif

		SDL_RenderPresent(ren);

		SDL_PollEvent(&e);

		if (e.type == SDL_QUIT)
		{
			quit = true;
		}

		gTime->ProgressCycle();

		int DeltaTime = (GetRealTimeMS() - CycleStart);
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
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}