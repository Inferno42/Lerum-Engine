#include "BattleManager.h"
#include "EGRP.h"

CBattleManager* BattleM = new CBattleManager();

CBattleManager::CBattleManager()
{
	Depth = -0.2f; //-0.2f because we still need to render text and sprites over it.
	dead = false;
	EntType = TYPE_OTHER; //We finally have a use for this enum!
	Solidity = TYPE_NONSOLID;
	Fade_Done = false;
}

CBattleManager::~CBattleManager()
{

}

void CBattleManager::Spawn()
{
	DrawBox.x = 0;
	DrawBox.y = 0;
	DrawBox.w = GlobEngine.GetGameScreen()->w;
	DrawBox.h = GlobEngine.GetGameScreen()->h;
	CurrentCrop = 0;
	for(int i = 0; i <= 7; ++i)
	{
		EntCoordsX[i] = 0;
		EntCoordsY[i] = 0;
	}

	EntCoordsX[0] = 150;
	EntCoordsX[1] = 300;
	EntCoordsX[2] = 450;
	EntCoordsX[3] = 600;
	EntCoordsX[4] = 150;
	EntCoordsX[5] = 300;
	EntCoordsX[6] = 450;
	EntCoordsX[7] = 600;

	for(int i = 0; i <= 3; ++i)
	{
		EntCoordsY[i] = 700;
	}

	for(int i = 4; i <= 7; ++i)
	{
		EntCoordsY[i] = 100;
	}

	

	BattleList.push_back(Player1);

	if(Player1->Companions[0]->IsActive() == true)
		BattleList.push_back(Player1->Companions[0]);

	if(Player1->Companions[1]->IsActive() == true)
		BattleList.push_back(Player1->Companions[1]);
	
	if(Player1->Companions[2]->IsActive() == true)
		BattleList.push_back(Player1->Companions[2]);

	Crops[0].x = 456;
	Crops[0].y = 1;
	Crops[0].w = 64;
	Crops[0].h = 64;


	Sprite = GraphicsM.Get_SpriteSheet(1).m_Sheet;
	SheetSize = GraphicsM.Get_SpriteSheet(1).size;

	Selected = 0;
	CurrentNumber = 0;

	ENT_INCREMENT(this);
}

void CBattleManager::Handle()
{
	if(BattleActive == true)
	{
		if(Delay < SDL_GetTicks() + 5000)
		{
		if(Fade_Done != true)
		{
			GraphicsM.Fade_Out();
			Fade_Done = true;
		}
		SetPos(gCam.GetCamera().x, gCam.GetCamera().y);
		BASE::Handle();
		}
	}
}

void CBattleManager::AddCombatant( CLivingEntity* Ent )
{
	BattleList.push_back(Ent);
	++CurrentNumber; //Keep track of current number of combatants.
}

void CBattleManager::StartBattle()
{
	/*
	for(int i = 0; i <= 3; ++i)
	{
		if(PlayerList[i] == NULL)
		{

		}
		else
		{
			if(PlayerList[i]->GetType() == TYPE_ENEMY)
			{
				//EnemyList[sizeof(EnemyList)] = CONVERT_ENT_TO_NPC(PlayerList[i]); //Okay, something weird happened. Possible Companion defunction? -Inferno
				
			}
		}
	}
	*/ // :(200): This will be re-enabled when the companion system is added.

	int b = BattleList.size();
	CLivingEntity* Buf = new CLivingEntity();
	for(int i = 0; i <= BattleList.size() - 1; ++i)
	{
		Buf = BattleList[i];
		if(BattleList[i]->GetType() == TYPE_ENEMY)
			EnemyList[0] = Buf;

		if(BattleList[i]->GetType() == TYPE_PLAYER)
			PlayerList[0] = Buf;
	}

	GraphicsM.Fade_In();
	BattleActive = true;
	Delay = SDL_GetTicks();
	//Player1->SetPos(EntCoordsX[0] * GraphicsM.GetResRatio(), EntCoordsY[0] * GraphicsM.GetResRatio());
	for(int i = 0; i <= BattleList.size() - 1; ++i )
	{
		if(BattleList[i] == NULL)
		{
			//Do nothing, this entity doesn't exist as far as we are concerned. - Inferno
		}
		else
		{
		//	BattleList[i]->SetPos(-gCam.GetCamera().x + EntCoordsX[i] * GraphicsM.GetResRatio() , 
			//	gCam.GetCamera().y +  EntCoordsY[i] * GraphicsM.GetResRatio());
			BattleList[i]->SetPos(EntCoordsX[i], EntCoordsY[i]);
			gCam.SetCamera(0, 0);
			BattleList[i]->SetDepth(-0.1f);

		}
	}
}

void CBattleManager::StopBattle()
{
	BattleActive = false;
}
