
#include "Wraith.h"
#include "Engine.h"
#include "GraphicManager.h"

CWraith::CWraith()
{
	Depth = -0.4;
	dead = false;
	Solidity = TYPE_SOLID;
	EntType = TYPE_ENEMY;
	Exemp = VIEW_UNEXEMPT;
	transparency = MaxTransparency;
		SizeRatio = 0.7f;
}

CWraith::~CWraith()
{

}

void CWraith::Spawn()
{
	Sprite = LOAD_TEXTURE("Person").m_Sheet;
	SheetSize = LOAD_TEXTURE("Person").size;
	
	CurrentCrop = 0;
	Crops[0].x = 270;
	Crops[0].y = 8;
	Crops[0].w = 52;
	Crops[0].h = 55;

	DrawBox.x = 0;
	DrawBox.y = 0;
	DrawBox.w = 52;
	DrawBox.h = 55;
	ScanCompleted = false;

	ENT_INCREMENT(this);
}

void CWraith::Handle()
{
	LoseVel();
	if(ScanCompleted == false)
	{
	for(int i = 0; i <= GlobEngine.GetEntityList().size() - 1 ; ++i)
	{
		if(GlobEngine.GetEntityList()[i]->GetType() == TYPE_PLAYER)
		{
			PlayerIndex = i;
			ScanCompleted = true;
			break;
		}
	}
	}
			CBaseEntity* tmpholder = GlobEngine.GetEntityList()[PlayerIndex];

		//	double ab = DistanceFrom(GetX(),GetY(),tmpholder->GetX(),tmpholder->GetY());
	//		DevInfo("DistanceFrom:%f",ab);
			if(DistanceFrom(GetX(),GetY(),tmpholder->GetX(),tmpholder->GetY()) < 200)
			{
				int a = DirectionTo(GetX(),GetY(),tmpholder->GetX(),tmpholder->GetY());
			/*	DevInfo ("Found him! He's %i of me!", a);
				DevInfo("Moving!");*/
				switch(a)
				{
				case 0:
					MoveLeft();
					break;
				case 1:
					MoveUp();
					MoveLeft();
					break;
				case 2:
					MoveUp();
					break;
				case 3:
					MoveRight();
					MoveUp();
					break;
				case 4:
					MoveRight();
					break;
				case 5:
					MoveDown();
					MoveRight();
					break;
				case 6:
					MoveDown();
					break;
				case 7:
					MoveLeft();
					MoveDown();
					break;
				}
			}
			else
			{
				BASE::Handle();
				return;
			}
		
	BASE::Handle();
}

void CWraith::MoveDown()
{
	yVel += .5f;
	if(yVel >= 3.5)
	{
		yVel = 3.5;
	}
	vector<CBaseEntity*> tmpVec;
	tmpVec = GlobEngine.GetEntityList();


	SetPos(GetX(), GetY() + yVel);
	for(int i = 0; i <= tmpVec.size() - 1; ++i)
	{
		if(SDL_CollideBoundingBox(DrawBox,tmpVec[i]->GetDrawBox()) == 1 && tmpVec[i]->GetSolidity() == TYPE_SOLID
			&& tmpVec[i]->GetIndex() != GetIndex() && GetSolidity() == TYPE_SOLID)
		{
#ifdef _DEBUG
			//DevInfo("Collision at X:%i Y:%i",GetX(), GetY());
#endif //_DEBUG
			if(tmpVec[i]->GetType() == TYPE_PLAYER)
			{
				TriggerBattle();
				SetPos(GetX(), GetY() - yVel - 1);
				yVel = 0;
			}
			else
			{
				SetPos(GetX(), GetY() - yVel - 1);
				yVel = 0;
			}
		}
	}
}

void CWraith::MoveLeft()
{
	xVel += .5f;
	if(xVel >= 3.5)
	{
		xVel = 3.5;
	}
	vector<CBaseEntity*> tmpVec;
	tmpVec = GlobEngine.GetEntityList();


	SetPos(GetX() - xVel, GetY());
	for(int i = 0; i <= tmpVec.size() - 1; ++i)
	{
		if(SDL_CollideBoundingBox(DrawBox,tmpVec[i]->GetDrawBox()) == 1 && tmpVec[i]->GetSolidity() == TYPE_SOLID
			&& tmpVec[i]->GetIndex() != GetIndex() && GetSolidity() == TYPE_SOLID)
		{
#ifdef _DEBUG
			//DevInfo("Collision at X:%i Y:%i",GetX(), GetY());
#endif //_DEBUG
			if(tmpVec[i]->GetType() == TYPE_PLAYER)
			{
			TriggerBattle();
			SetPos(GetX() + xVel + 1, GetY());
			xVel = 0;
			}
			else
			{
				SetPos(GetX() + xVel + 1, GetY());
				xVel = 0;
			}
		}
	}
}

void CWraith::MoveRight()
{
	xVel += .5f;
	if(xVel >= 3.5)
	{
		xVel = 3.5;
	}
	vector<CBaseEntity*> tmpVec;
	tmpVec = GlobEngine.GetEntityList();


	SetPos(GetX() + xVel, GetY());
	for(int i = 0; i <= tmpVec.size() - 1; ++i)
	{
		if(SDL_CollideBoundingBox(DrawBox,tmpVec[i]->GetDrawBox()) == 1 && tmpVec[i]->GetSolidity() == TYPE_SOLID
			&& tmpVec[i]->GetIndex() != GetIndex() && GetSolidity() == TYPE_SOLID)
		{
#ifdef _DEBUG
			//DevInfo("Collision at X:%i Y:%i",GetX(), GetY());
#endif //_DEBUG
			if(tmpVec[i]->GetType() == TYPE_PLAYER)
			{
				TriggerBattle();
			SetPos(GetX() - xVel - 1, GetY());
			xVel = 0;
			}
			else
			{
				SetPos(GetX() - xVel - 1, GetY());
				xVel = 0;
			}
		}
	}	
}

void CWraith::MoveUp()
{
	yVel += .5f;
	if(yVel >= 3.5)
	{
		yVel = 3.5;
	}
	vector<CBaseEntity*> tmpVec;
	tmpVec = GlobEngine.GetEntityList();


	SetPos(GetX(), GetY() - yVel);
	for(int i = 0; i <= tmpVec.size() - 1; ++i)
	{
		if(SDL_CollideBoundingBox(DrawBox,tmpVec[i]->GetDrawBox()) == 1 && tmpVec[i]->GetSolidity() == TYPE_SOLID
			&& tmpVec[i]->GetIndex() != GetIndex() && GetSolidity() == TYPE_SOLID)
		{
#ifdef _DEBUG
			//DevInfo("Collision at X:%i Y:%i",GetX(), GetY());
#endif //_DEBUG
			if(tmpVec[i]->GetType() == TYPE_PLAYER)
			{
			TriggerBattle();
			SetPos(GetX(), GetY() + yVel + 1);
			yVel = 0;
			}
			else
			{
				SetPos(GetX(), GetY() + yVel + 1);
				yVel = 0;
			}
		}
	}
}

void CWraith::LoseVel()
{
	xVel -= .1f;
	yVel -= .1f;
	if(xVel < 0)
	{
		xVel = 0;
	}

	if(yVel < 0)
	{
		yVel = 0;
	}
}

void CWraith::TriggerBattle()
{
	CBaseNPC::TriggerBattle();
}
