#include "Player.h"
#include "EGRP.h"
#include <stack>

CPlayer* Player1;

CPlayer::CPlayer()
{
	CurrentCompanionMax = 0; // :(200): System currently disabled.
	Depth = -0.4;
	dead = false;
	xVel = 0;
	yVel = 0;
	
	Solidity = TYPE_SOLID;
	EntType = TYPE_PLAYER;
	health = 100;
	transparency = 0.0f;
	maxvl = 5.0;
	SizeRatio = 0.7f;
	Exemp = VIEW_UNEXEMPT;
	Inventory = new CInventory();
}

CPlayer::~CPlayer()
{
	
}

void CPlayer::Spawn()
{
	Sprite = LOAD_TEXTURE("128Dev").m_Sheet;
	SheetSize = LOAD_TEXTURE("128Dev").size;
	CurrentCrop = 0;
	Crops[0].x = 31;
	Crops[0].y = 41;
	Crops[0].w = 63;
	Crops[0].h = 88;
	
	DrawBox.x = 0;
	DrawBox.y = 0;
	DrawBox.w = 63;
	DrawBox.h = 88;
	
	Companions[0] = new CBaseNPC();
	Companions[1] = new CBaseNPC();
	Companions[2] = new CBaseNPC();

	stats.ResetAll();

	ENT_INCREMENT(this);
}

void CPlayer::Handle()
{
	BASE::Handle();
	////DevInfo("X:%d Y:%d",GetX(),GetY());
}

void CPlayer::Use()
{
	vector<CBaseEntity*> tmpVec;
	tmpVec = GlobEngine.GetEntityList();

	for(int i = 0; i <= tmpVec.size() - 1; ++i)
	{
		if(tmpVec[i]->GetType() == TYPE_ITEM && DistanceFrom(tmpVec[i]->GetX(), 
			tmpVec[i]->GetY(), GetX(), GetY()) <= DrawBox.w + DrawBox.h)
		{
			CItem* tmp = (CItem*)tmpVec[i];
			tmp->Handle_Item_Effect();
			break;
		}
	}
}

void CPlayer::MoveLeft()
{
	xVel += .5f;
	if(xVel >= maxvl)
	{
		xVel = maxvl;
	}
	vector<CBaseEntity*> tmpVec;
	tmpVec = GlobEngine.GetEntityList();


	SetPos(GetX() - xVel, GetY());
	for(int i = 0; i <= tmpVec.size() - 1; ++i)
	{

	if(SDL_CollideBoundingBox(DrawBox,tmpVec[i]->GetDrawBox()) == 1 && tmpVec[i]->GetSolidity() == TYPE_SOLID && tmpVec[i]
	->GetType() != TYPE_PLAYER)
	{
#ifdef _DEBUG
		//DevInfo("Collision at X:%i Y:%i",GetX(), GetY());
#endif //_DEBUG
		SetPos(GetX() + xVel + 1, GetY());
		xVel = 0;
		
	}
	}
}

void CPlayer::MoveRight()
{
	xVel += .5f;
	if(xVel >= maxvl)
	{
		xVel = maxvl;
	}
	vector<CBaseEntity*> tmpVec;
	tmpVec = GlobEngine.GetEntityList();


	SetPos(GetX() + xVel, GetY());
	for(int i = 0; i <= tmpVec.size() - 1; ++i)
	{
		if(SDL_CollideBoundingBox(DrawBox,tmpVec[i]->GetDrawBox()) == 1 && tmpVec[i]->GetSolidity() == TYPE_SOLID && tmpVec[i]
		->GetType() != TYPE_PLAYER)
		{
#ifdef _DEBUG
			//DevInfo("Collision at X:%i Y:%i",GetX(), GetY());
#endif //_DEBUG
			SetPos(GetX() - xVel - 1, GetY());
			xVel = 0;
		}
	}
}

void CPlayer::MoveUp()
{
	yVel += .5f;
	if(yVel >= maxvl)
	{
		yVel = maxvl;
	}
	vector<CBaseEntity*> tmpVec;
	tmpVec = GlobEngine.GetEntityList();

	
	SetPos(GetX(), GetY() - yVel);
	for(int i = 0; i <= tmpVec.size() - 1; ++i)
	{
		if(SDL_CollideBoundingBox(DrawBox,tmpVec[i]->GetDrawBox()) == 1 && tmpVec[i]->GetSolidity() == TYPE_SOLID && tmpVec[i]
		->GetType() != TYPE_PLAYER)
		{
#ifdef _DEBUG
			//DevInfo("Collision at X:%i Y:%i",GetX(), GetY());
#endif //_DEBUG
			SetPos(GetX(), GetY() + yVel + 1);
			yVel = 0;
		}
	}
}

void CPlayer::MoveDown()
{
	yVel += .5f;
	if(yVel >= maxvl)
	{
		yVel = maxvl;
	}
	vector<CBaseEntity*> tmpVec;
	tmpVec = GlobEngine.GetEntityList();


	SetPos(GetX(), GetY() + yVel);
	for(int i = 0; i <= tmpVec.size() - 1; ++i)
	{
		if(SDL_CollideBoundingBox(DrawBox,tmpVec[i]->GetDrawBox()) == 1 && tmpVec[i]->GetSolidity() == TYPE_SOLID && tmpVec[i]
		->GetType() != TYPE_PLAYER)
		{
#ifdef _DEBUG
			//DevInfo("Collision at X:%i Y:%i",GetX(), GetY());
#endif //_DEBUG
			SetPos(GetX(), GetY() - yVel - 1);
			yVel = 0;
		}

	}
}

void CPlayer::LoseVel()
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

void CPlayer::AddCompanion( CBaseNPC* ent )
{
	if(CurrentCompanionMax < 3)
	{
		Companions[CurrentCompanionMax] = ent;
		++CurrentCompanionMax;
	}
}

void CPlayer::RemoveCompanion( int ID )
{
	--CurrentCompanionMax;
	Companions[ID] = NULL;
}
