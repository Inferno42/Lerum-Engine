#ifndef ITEM_H
#define ITEM_H
#include "Definitions.h"

struct IStats
{
	string name;
};

#include "BaseClass.h"

class CItem : public CBaseEntity
{
	public:
		CItem() {};
		~CItem() {};

		virtual void Handle_Item_Effect() {};

	protected:
		IStats itemstats;
		unsigned long InvID;
}; 
#endif // ITEM_H