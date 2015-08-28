#ifndef PLAYER_H
#define PLAYER_H
#include "LivingEntity.h"
#include "BaseNPC.h"
#include "InventorySystem.h"

class CPlayer : public CLivingEntity
{
public:
	CPlayer();
	~CPlayer();
	virtual void Spawn();
	virtual void Handle();
	void MoveRight();
	void MoveLeft();
	void MoveUp();
	void MoveDown();
	void LoseVel();
	void Use();
	void SetMaxSpeed(float spd) {maxvl = spd;}
	float GetMaxVel() {return maxvl;}

	float GetVel() {return xVel + yVel;}
	float GetxVel() {return xVel;}
	float GetyVel() {return yVel;}

	void AddCompanion(CBaseNPC* ent);
	void RemoveCompanion(int ID);
	
	CBaseNPC* Companions[3];

	CInventory* Inventory;

private:
	int CurrentCompanionMax;
	float xVel;
	float yVel;
	float maxvl;
}; extern CPlayer* Player1;

#endif // PLAYER_H