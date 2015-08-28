#include "InteractiveEnt.h"
#include "Engine.h"
#include "GraphicManager.h"

CInteractiveEntity::CInteractiveEntity()
{

}

void CInteractiveEntity::Handle()
{
	int x, y;
	SDL_GetMouseState(&x,&y);
	SDL_Rect tmprect = {x, y, 16, 16};

			if(SDL_CollideBoundingBox(tmprect, DrawBox))
			{
				if(SDL_PollEvent(&event))
				{
					if(event.type == SDL_MOUSEBUTTONDOWN)
					{
						Press();
					}

					if(event.type == SDL_MOUSEMOTION)
					{
						Hover();
					}
				}
			}
	//GRAPHICS_QUEUE_INCREMENT(this);
	BASE::Handle();
}

void CInteractiveEntity::Hover()
{
	//DevInfo("Current Index:%i", GetIndex());
}

void CInteractiveEntity::Press()
{
#ifdef _DEBUG
	DevInfo("Pressed!");
#endif
}

void CInteractiveEntity::Spawn(int X, int Y)
{
	Crops[0].x = 1;
	Crops[0].y = 1;
	Crops[0].w = 31;
	Crops[0].h = 31;

	Crops[1].x = 33;
	Crops[1].y = 1;
	Crops[1].w = 31;
	Crops[1].h = 31;

	Crops[2].x = 65;
	Crops[2].y = 1;
	Crops[2].w = 31;
	Crops[2].h = 31;

	CurrentCrop = 0;

	SDL_Rect Bx;
	Bx.x = X;
	Bx.y = Y;
	Bx.w = 512;
	Bx.h = 512;
	this->SetDrawBox(Bx);

	//Sheet tmp = GraphicsM.Get_SpriteSheet(SHEET_BINARY);
	//this->SheetSize = tmp.size;
//	this->SetSprite(tmp.m_Sheet);
	ENT_INCREMENT(this);
}