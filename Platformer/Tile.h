#ifndef TILE_H
#define TILE_H
#include "BaseClass.h"

class CTile : public CBaseEntity
{
	public:
		CTile();
		~CTile();
		virtual void Spawn();
		virtual void Handle();
};

#endif // TILE_H