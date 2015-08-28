#pragma once
#ifndef BASENPC_H
#define BASENPC_H
#include "LivingEntity.h"

class CBaseNPC : public CLivingEntity
{
	public:
		CBaseNPC();

		virtual void TriggerBattle();
		bool IsActive() {return Active;}

	private:
		bool Active;
};

#endif // BASENPC_H