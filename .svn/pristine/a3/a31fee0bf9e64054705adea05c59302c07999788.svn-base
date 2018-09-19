#ifndef ACTORCOLLISION_H
#define ACTORCOLLISION_H

#include "Utils.h"
#include "Console.h"
#include "DiagnosticDraw.h"
#include "Event.h"
#include "Actor.h"
#include "ActorHandle.h"

#define MAX_ACTORS 1024

#define CELLS_X 10
#define	CELLS_Y 2
#define CELL_COUNT (CELLS_X*CELLS_Y)

class Cell
{
public:
	Cell() : mCell_Rect()
	{
		mActors_In_Cell = BinaryTree();
	}

	Cell(SDL_Rect rect) : mCell_Rect(rect)
	{
		mActors_In_Cell = BinaryTree();
	}

	SDL_Rect* GetCellRect()
	{
		return &mCell_Rect;
	}

	BinaryTree* GetActorTree()
	{
		return &mActors_In_Cell;
	}
protected:
	SDL_Rect mCell_Rect;
	BinaryTree mActors_In_Cell;
};

class SpatialMonitor : public EventReceiver
{
public:

	SpatialMonitor()
	{
	}

	SpatialMonitor(int worldH, int worldW, ActorHandleManager* AHM) : mAHM(AHM)
	{
		PartitionCells(worldH, worldW);
	}

	int GetAdjacentCells(int cellnum, Cell* cells[9]);

	bool LogActor(int id); //Logs an actor with the spatial monitor. called on program startup

	bool EventProcess(Event eve);

	Cell* GetCell(int i) //Gets the cell from a cell number. 
	{
		if ((0 <= i) && (i < CELL_COUNT))
		{
			return &mCells[i]; 
		}
		else 
		{
			//gCons->ConsPrintf("Cell %i does not exist\n", i)
			return NULL; 
		}
	}

protected:

	bool PartitionCells(int worldH, int worldW); //divides the level into cells based on macro'd parameters

	//bool GetActorsInCell(int cellnum);

	//bool GetAdjacentActors(int cellnum);

	bool DetectActorCollision(int id1, int id2); //checks two logged actors for intersection

	bool DetectRectSensors(SDL_Rect* sensor, int detectorID, int foreignID); //Called in HandleRectSensors, checks given rectangle for intersects

	bool ClearActorCell(int id);

	int UpdateActorCell(int id); //Updates the the cell number that contains a logged actor, Called when an MOVED_THIS_FRAME event is processed

	int GetActorCell(int id) //Gets the cell number of an actor
	{

		return (mAHM->GetActorAddress(id)->GetSpatCell());
		
		//return mActorCells[id];
	}

	//int* GetAdjacentCells(int cellnum, int cells[9]); //populates and returns cells[9] with the cell numbers of cellnum and the 8 surrounding cells

	bool HandleCollisions(int CallerID); //Called in event process, finds the actors in the cells adjacent to the cell of CallerID and checks them for collision with CallerID
	
	bool HandleRectSensors(SDL_Rect* sensor, int CallerID, SensorType SeType);

	bool TestBlockers(SDL_Rect* sensor, int CallerID);


	//BinaryTree mActors;
	ActorHandleManager* mAHM;
	//int mActorCells[MAX_ACTORS];
	Cell mCells[CELL_COUNT];
	//int mActorCount;
	//int mAdjacentActorIDs[MAX_ACTORS];
	//int mAdjacentActorCount;
};

#endif

