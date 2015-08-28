#ifndef WRAITH_H 
#define WRAITH_H
#include "Definitions.h"
#include "BaseNPC.h"

class CWraith : public CBaseNPC
{
	public:
		CWraith();
		~CWraith();

		virtual void Spawn();
		virtual void Handle();

		void MoveLeft();
		void MoveRight();
		void MoveUp();
		void MoveDown();
		void LoseVel();


		float GetVel() {return xVel + yVel;}

		virtual void TriggerBattle();

private:
	float xVel;
	float yVel;
	int PlayerIndex;
	bool ScanCompleted;
};
#endif //WRAITH_H