#include "BaseNPC.h"
#include "BattleManager.h"

CBaseNPC::CBaseNPC()
{
	Active = false;
	Exemp = true;
}


void CBaseNPC::TriggerBattle()
{
	BattleM->AddCombatant(this);
	BattleM->StartBattle();
}


CBaseNPC* UTIL_CBE2CBNPC(CBaseEntity* b )
{
	CBaseNPC* a = NULL;

	return a;
}