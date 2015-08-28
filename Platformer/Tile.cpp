#include "Tile.h"
#include "Engine.h"

CTile::CTile()
{
	Depth = -0.5;
	dead = false;
	SizeRatio = 0.7f;
	Exemp = VIEW_UNEXEMPT;
}

CTile::~CTile()
{

}

void CTile::Spawn()
{
	ENT_INCREMENT(this);
}

void CTile::Handle()
{
	BASE::Handle();
}