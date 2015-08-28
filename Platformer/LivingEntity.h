#ifndef LIVING_ENTITY_H
#define LIVING_ENTITY_H
#include "BaseClass.h"
#include "StatSystem.h"

//This class is a WIP, dialog reading, cutscenes, etc will be added later.
//This class is also used mainly as a sorter and an up-inherit. (Child -> Parent)
class CLivingEntity : public CBaseEntity
{
public:
	CLivingEntity() {};

	int GetHealth() {return health;}
	void AddHealth(int nh) {health += nh;}
	void DecHealth(int nh) {health -= nh;}

protected:
	int health;
	CStatSystem stats;
};

#endif //LIVING_ENTITY_H