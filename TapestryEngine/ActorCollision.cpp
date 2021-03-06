#include "ActorCollision.h"

bool SpatialMonitor::PartitionCells(int worldH, int worldW)
{
	int cellW = (worldW / CELLS_X);
	int cellH = (worldH / CELLS_Y);

	for (int i = 0; i < CELLS_Y; i++)
	{
		for (int j = 0; j < CELLS_X; j++)
		{
			Cell new_cell;
			new_cell.GetCellRect()->w = cellW;
			new_cell.GetCellRect()->h = cellH;
			new_cell.GetCellRect()->x = cellW * j;
			new_cell.GetCellRect()->y = cellH * i;

			mCells[i*CELLS_X + j] = new_cell;

		}
	}
	return true;
}

bool SpatialMonitor::LogActor(int id)
{
	//mActors[mActorCount] = &act;
	//mActors.Insert(act.GetHandle(), &act);
	//act.SetSpatID(mActorCount);
	UpdateActorCell(id);
	return true;
}

bool SpatialMonitor::ClearActorCell(int id)
{
	if ((id == 7) | (id == 8))
	{
		gCons->ConsPrintf("seal updates cell\n");
	}
	if (id == 9)
	{
		gCons->ConsPrintf("player updates cell\n");
	}
	
	if (GetActorCell(id) != -1)
	{
		//mCells[GetActorCell(id)].GetActorTree()->Search(id)->Delete();
		mCells[GetActorCell(id)].GetActorTree()->DeleteNode(id);
		return true;
	}
	return false;
}


int SpatialMonitor::UpdateActorCell(int id)
{
	//if (id == 7)
	//{
	//	gCons->ConsPrintf("seal updates cell\n");
	//}
	Actor* act = (mAHM->GetActorAddress(id));
	for (int i = 0; i < CELL_COUNT; i++)
	{
		if (DetectCenterPointIntersect( mCells[i].GetCellRect(),  act->GetPosition() ) )
		{
			//gCons->ConsPrintf("Actor entering cell %i\n", i);
			
			if (i != act->GetSpatCell())
			{
				mCells[i].GetActorTree()->Insert(id, NULL);
				ClearActorCell(id); 
				act->SetSpatCell(i);
			}

			return i;
		}
	}
	gCons->ConsPrintf("Could not find Actor cell\n");
	return -1;
}

int SpatialMonitor::GetAdjacentCells(int cellnum, Cell* cells[9])
{
	cells[0] = GetCell((cellnum - CELLS_X - 1));
	cells[1] = GetCell((cellnum - CELLS_X));
	cells[2] = GetCell((cellnum - CELLS_X + 1));

	cells[3] = GetCell((cellnum - 1));
	cells[4] = GetCell((cellnum));
	cells[5] = GetCell((cellnum + 1));
	
	cells[6] = GetCell((cellnum + CELLS_X - 1));
	cells[7] = GetCell((cellnum + CELLS_X));
	cells[8] = GetCell((cellnum + CELLS_X + 1));

	return 0;
}

//bool SpatialMonitor::GetActorsInCell(int cellnum) //uneeded now. Use Cell.GetActorTree()
//{
//	for (int i = 0; i < MAX_ACTORS; i++) //this is very bad. Basically defeats the function of cells by check each actor
//	{
//		if (mActorCells[i] == cellnum)
//		{
//			//gCons->ConsPrintf("Actor %i is in adjacent cell\n", i);
//			mAdjacentActorIDs[mAdjacentActorCount] = i;
//			mAdjacentActorCount++;
//		}
//	}
//	return true;
//}

//bool SpatialMonitor::GetAdjacentActors(int cellnum)
//{
//	mAdjacentActorCount = 0;
//	mAdjacentActorIDs[MAX_ACTORS] = { 0 };
//
//	int cells[9];
//	GetAdjacentCells(cellnum, cells);
//
//	for (int i = 0; i < 9; i++)
//	{
//		GetActorsInCell(cells[i]);
//		//gDiagDraw->LogDiagRect(mCells[cells[i]]);
//	}
//	return true;
//}

bool SpatialMonitor::DetectActorCollision(int id1, int id2)
{
	if (id1 != id2)
	{	
		//gDiagDraw->LogDiagRect(*mActors[id2]->GetPosition());
		return DetectRectIntersect(mAHM->GetActorAddress(id1)->GetPosition(), mAHM->GetActorAddress(id2)->GetPosition());
	}
	else
	{
		//gCons->ConsPrintf("Attempted to check actor collision with itself\n");
		return false;
	}
}

bool SpatialMonitor::DetectRectSensors(SDL_Rect* sensor, int DetectorID, int foreignID)
{
	if (DetectorID != foreignID)
	{
		//gDiagDraw->LogDiagRect(*sensor);
		//gDiagDraw->LogDiagRect(*mActors[foreignID]->GetPosition());
		return DetectRectIntersect(sensor, mAHM->GetActorAddress(foreignID)->GetPosition());
	}
	else
	{
		//gCons->ConsPrintf("Attempted to check actor collision with itself\n");
		return false;
	}
}

bool SpatialMonitor::HandleCollisions(int CallerID)
{

	int CallerCell = GetActorCell(CallerID);
	
	Cell* AdjecentCellIndex[9];
	GetAdjacentCells(CallerCell, AdjecentCellIndex);

	for (int i = 0; i < 9; i++)
	{	
		if (AdjecentCellIndex[i] != NULL)
		{
			int array_size = AdjecentCellIndex[i]->GetActorTree()->Size();
			if (array_size != -1)
			{
				//Node** ActorTreeArray = NULL;
				Node** ActorTreeArray = new Node*[array_size];
				ActorTreeArray = (AdjecentCellIndex[i]->GetActorTree())->Dump();
				for (int j = 0; j < (array_size); j++)
				{
					if (ActorTreeArray[j] == (Node*)(0xcdcdcdcd))
					{
						gCons->ConsPrintf("uninitialized memory\n");
						AdjecentCellIndex[i]->GetActorTree()->Dump();
					}
					assert(j <= array_size);
					//gCons->ConsPrintf("index: %i, item: %i\n", j, ActorTreeArray[j]->GetItem());	
					int size = sizeof(ActorTreeArray);

					if (ActorTreeArray[j] == NULL)
					{
						gCons->ConsPrintf("Error: invalid index into actor tree, Cell: %i", i);
					}
					if (DetectActorCollision(CallerID, ActorTreeArray[j]->GetItem()) == true)
					{
						mAHM->GetActorAddress(CallerID)->EventProcess(Event(ACTOR_COLLISION, ActorTreeArray[j]->GetItem()));
					}
				}
			}
			else
			{
				//gCons->ConsPrintf("Cell is empty/n");
			}
		}
		else
		{
			//Cell does not exist. do nothing
		}
	}

	return true;
}

bool SpatialMonitor::HandleRectSensors(SDL_Rect* sensor, int CallerID, SensorType SeType)
{
	
	int CallerCell = GetActorCell(CallerID);

	Cell* AdjecentCellIndex[9];
	GetAdjacentCells(CallerCell, AdjecentCellIndex);

	for (int i = 0; i < 9; i++)
	{
		if (AdjecentCellIndex[i] != NULL)
		{
			int array_size = AdjecentCellIndex[i]->GetActorTree()->Size();
			if (array_size != -1)
			{
				//Node** ActorTreeArray = NULL;
				Node** ActorTreeArray = new Node*[array_size];
				ActorTreeArray = (AdjecentCellIndex[i]->GetActorTree())->Dump();
				for (int j = 0; j < (array_size); j++)
				{
					assert(j <= array_size);
					//gCons->ConsPrintf("index: %i, item: %i\n", j, ActorTreeArray[j]->GetItem());

					if (ActorTreeArray[j] == NULL)
					{
						gCons->ConsPrintf("Error: invalid index into actor tree, Cell: %i", i);
					}
					if (DetectRectSensors(sensor, CallerID, ActorTreeArray[j]->GetItem()) == true)
					{
						mAHM->GetActorAddress(CallerID)->EventProcess(Event(SENSOR_COLLISION, SeType, ActorTreeArray[j]->GetItem())); //Used to pass actor* now passed ID number. receiver functions need to be updated
					}
				}
			}
			else
			{
				//gCons->ConsPrintf("Cell is empty/n");
			}
		}
		else
		{
			//Cell does not exist. do nothing
		}
	}
	return true;
}

bool SpatialMonitor::TestBlockers(SDL_Rect* sensor, int CallerID)
{	
	int CallerCell = GetActorCell(CallerID);

	Cell* AdjecentCellIndex[9];
	GetAdjacentCells(CallerCell, AdjecentCellIndex);

	for (int i = 0; i < 9; i++)
	{
		if (AdjecentCellIndex[i] != NULL)
		{
			Node** ActorTreeArray = ((AdjecentCellIndex[i]->GetActorTree())->Dump());
			if (ActorTreeArray != NULL)
			{
				for (int j = 0; j < (AdjecentCellIndex[i]->GetActorTree())->Size(); j++)
				{
					if (DetectRectSensors(sensor, CallerID, ActorTreeArray[j]->GetItem()) == true)
					{
						if (mAHM->GetActorAddress(ActorTreeArray[j]->GetItem())->IsBlocking() == true)
						{
							return true;
						}
					}
				}
			}
			else
			{
				//gCons->ConsPrintf("Cell is empty/n");
			}
		}
		else
		{
			//Cell does not exist. do nothing
		}
	}
	return false;
}

bool SpatialMonitor::EventProcess(Event eve)
{
	switch (*eve.GetEventType())
	{
	case MOVED_THIS_FRAME:
		UpdateActorCell(eve.GetEventData()->i);
		HandleCollisions(eve.GetEventData()->i);
		return true;
		break;
	case CHECK_RECT_SENSOR:
		HandleRectSensors(eve.GetEventData()->sd.sensor, eve.GetEventData()->sd.id, eve.GetEventData()->sd.st);
		return true;
		break;
	case CHECK_BLOCKERS:
		return TestBlockers(eve.GetEventData()->sd.sensor, eve.GetEventData()->sd.id);
		break;
	default:
		gCons->ConsPrintf("Spatial Monitor Received Invalid Event Type\n");
		return false;
		break;
	}
}