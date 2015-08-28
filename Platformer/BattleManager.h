#pragma once
#ifndef BATTLEMANAGER_H
#define BATTLEMANAGER_H

#include "LivingEntity.h"
#include "DaemonClass.h"
#include "TextHandler.h"

class CBattleManager : public CDaemonEntity
{
	public:
		CBattleManager();
		~CBattleManager();

		virtual void Spawn();
		virtual void Handle();
		void AddCombatant(CLivingEntity* Ent);
		void StartBattle();
		void StopBattle();

	private:
		int EntCoordsX[7]; // Player1, Companion1, Campanion2, Companion3, Enemy1, Enemy2, Enemy3, Enemy4 (0-7)
		int EntCoordsY[7]; // Player1, Companion1, Campanion2, Companion3, Enemy1, Enemy2, Enemy3, Enemy4 (0-7)
		int Selected;
		int CurrentNumber;
		float Delay;
		bool Fade_Done;
		bool BattleActive;
		CLivingEntity* PlayerList[4];
		CLivingEntity* EnemyList[4];
		vector<CLivingEntity*> BattleList; //A list of all entities, entities first added here before being sorted.
		CTextHandler FMan;
}; extern CBattleManager* BattleM;

#endif //BATTLEMANAGER_H