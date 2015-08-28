#pragma once
#ifndef ENGINE_H
#define ENGINE_H
#include "Definitions.h"
#include "GameStateHandler.h"
#include "InputManager.h"
#include "BaseClass.h"
#include "GraphicManager.h"
#include "Player.h"
#include "TileManager.h"
#include "Menu.h"

class Engine
{

	public:
		Engine();
		bool BootGL(); 
		bool InitWindow();
		bool StartUp();
		bool MainLoop();
		bool SetupAudio();
		bool SetupLevels();
		bool DisableVSync();
		void Add_To_Ent_List(CBaseEntity* ent);
		SDL_Surface* GetGameScreen() { return Window; }
		vector<CBaseEntity*> GetEntityList() {return EntList;}
		void Handle_EntList();

		void ResetScreen(int w, int h) {Window = SDL_SetVideoMode(w, h, 32, SDL_OPENGL | SDL_RESIZABLE);}

		CMenu* GetMenu() {return Menu;}

		void HandleRes();

		static void TestCall() 
		{
			#ifdef _DEBUG 
			DevDrop("YAY!");
			#endif
		}

private:
		double ResTmp;
		bool Active;
		InputManager Input;
		vector<CBaseEntity*> EntList;
		SDL_Surface* Window;
		CTileManager TileMan;

} extern GlobEngine;

#define ENT_INCREMENT(Entity); Entity->SetIndex(GlobEngine.GetEntityList().size() + 1); GlobEngine.Add_To_Ent_List(Entity);  


#endif // ENGINE_H

