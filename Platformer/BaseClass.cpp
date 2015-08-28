#include "BaseClass.h"
#include "Engine.h"
#include "GraphicManager.h"

CBaseEntity::CBaseEntity(int X, int Y)
{
	SheetSize = 0;
	transparency = 0.0f;
	Depth = -0.4;
	dead = false;
	SizeRatio = 0.7f;
	customheight = false;
	HasShader = false;
	shadname = "";
}

CBaseEntity::CBaseEntity()
{
	SheetSize = 0;
	transparency = 0.0f;
	Depth = -0.4;
	dead = false;
}

CBaseEntity::~CBaseEntity()
{
//	delete[] Crops;
}

void CBaseEntity::Spawn( int X, int Y )
{
	Crops[0].x = 1;
	Crops[0].y = 1;
	Crops[0].w = 31;
	Crops[0].h = 31;

	CurrentCrop = 0;

	SDL_Rect Bx;
	Bx.x = X;
	Bx.y = Y;
	Bx.w = 33;
	Bx.h = 16;
	this->SetDrawBox(Bx);
	ENT_INCREMENT(this);
}

void CBaseEntity::Handle()
{
	GraphicsM.Add_To_Draw_Queue(this);
}

bool CBaseEntity::Check_Collison(SDL_Rect* CollidingRect)
{
	if(BoundBox.y + BoundBox.h <= CollidingRect->y)
	{
		return true;
	}

	if(BoundBox.y >= CollidingRect->y + CollidingRect->h)
	{
		return true;
	}

	if(BoundBox.x + BoundBox.w <= CollidingRect->x)
	{
		return true;
	}

	if(BoundBox.x >= CollidingRect->x + CollidingRect->w)
	{
		return true;
	}

	return false;
}

void CBaseEntity::Remove_Entity()
{
	dead = true;
}
/*

void CBaseEntity::SetDrawBox( SDL_Rect newrect )
{
	DrawBox.x = newrect.x - gCam.GetCamera().x;
	DrawBox.y = newrect.y - gCam.GetCamera().y;
}
*/
