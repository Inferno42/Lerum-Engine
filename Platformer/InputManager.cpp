#include "InputManager.h"
#include "Engine.h"
#include "Camera.h"


InputManager::InputManager()
{
	Time = 0;
}

void quit()
{
	#ifdef _DEBUG
	DevInfo("Quit event detected! Shutting down!");
	SDL_Delay(3000);
	#endif // _DEBUG
	SDL_Quit();
	SDL_Delay(100);
	exit(0);
}

void InputManager::HandleInput()
{
	Player1->LoseVel();

	while(SDL_PollEvent(&event))
	{
		Handle_DEBUG();

		if(GameStateH.GetCurrentState() == STATE_ACTIVE)
		{
		Handle_Player_Input();
		}
	//	else if(GameStateH.GetCurrentState() == STATE_MENU)
		//{
	//	Handle_Menu_Input(); why is this commented? -bg
	//	}
		else if(GameStateH.GetCurrentState() == STATE_CUTSCENE)
		{

		}

	
			
		
	}
}

void InputManager::Handle_Player_Input()
{
	if(event.key.keysym.sym == SDLK_LEFTBRACKET)
	{
		GraphicsM.ShaderController.ReloadShader("test");
	}

	if(event.key.keysym.sym == SDLK_ESCAPE && Time <= SDL_GetTicks() + 5000)
	{
	//	GameStateH.SetGameState(STATE_MENU);
	//	Menu->Visible = true;
	//	Time = SDL_GetTicks();
	}
	if(event.key.keysym.sym == SDLK_a)
	{
		Player1->MoveLeft();
		if(GraphicsM.GetResRatio() >= 1.0f)
		{
/*
			gCam.SetCamera((Player1->GetX() - (GlobEngine.GetGameScreen()->w / 2 * GraphicsM.GetResRatio())) - Player1->GetxVel() ,
				(Player1->GetY() - (GlobEngine.GetGameScreen()->h / 2) * GraphicsM.GetResRatio()) );*/
			gCam.SetCamera((Player1->GetX() - (GlobEngine.GetGameScreen()->w / 2)) / GraphicsM.GetResRatio() - Player1->GetxVel(), 
				(Player1->GetY() - (GlobEngine.GetGameScreen()->h / 2)) * GraphicsM.GetResRatio() );

		}
		else
		{
			gCam.SetCamera((Player1->GetX() - (GlobEngine.GetGameScreen()->w / 2)), //* GraphicsM.GetResRatio(), //+ Player1->GetxVel(), 
				(Player1->GetY() - (GlobEngine.GetGameScreen()->h / 2)) );
		}
	}

	if(event.key.keysym.sym == SDLK_d)
	{

		Player1->MoveRight();
		if(GraphicsM.GetResRatio() >= 1.0f)
		{
			gCam.SetCamera((Player1->GetX() - (GlobEngine.GetGameScreen()->w / 2 * GraphicsM.GetResRatio())) , 
				(Player1->GetY() - (GlobEngine.GetGameScreen()->h / 2) * GraphicsM.GetResRatio()) );
		}
		else
		{
			gCam.SetCamera((Player1->GetX() - (GlobEngine.GetGameScreen()->w / 2)) , 
				(Player1->GetY() - (GlobEngine.GetGameScreen()->h / 2)) );
		}
	}
	if(event.key.keysym.sym == SDLK_w)
	{

		Player1->MoveUp();
		if(GraphicsM.GetResRatio() >= 1.0f)
		{
		gCam.SetCamera((Player1->GetX() - (GlobEngine.GetGameScreen()->w / 2 * GraphicsM.GetResRatio())) , 
			(Player1->GetY() - (GlobEngine.GetGameScreen()->h / 2) * GraphicsM.GetResRatio()) );
		}
		else
		{
			gCam.SetCamera((Player1->GetX() - (GlobEngine.GetGameScreen()->w / 2)) , 
				(Player1->GetY() - (GlobEngine.GetGameScreen()->h / 2)) );
		}
	}
	if(event.key.keysym.sym == SDLK_s)
	{

		Player1->MoveDown();
		if(GraphicsM.GetResRatio() >= 1.0f)
		{
			gCam.SetCamera((Player1->GetX() - (GlobEngine.GetGameScreen()->w / 2 * GraphicsM.GetResRatio())) , 
				(Player1->GetY() - (GlobEngine.GetGameScreen()->h / 2) * GraphicsM.GetResRatio()) );
		}
		else
		{
			gCam.SetCamera((Player1->GetX() - (GlobEngine.GetGameScreen()->w / 2)) , 
				(Player1->GetY() - (GlobEngine.GetGameScreen()->h / 2)) );

		}
	}

	if(event.key.keysym.sym == SDLK_e)
	{
		Player1->Use();
	}

	if(event.type == SDL_QUIT)
	{
		quit();
	}
}

void InputManager::Handle_DEBUG()
{
	if(event.type == SDL_VIDEORESIZE)
	{
		SDL_FreeSurface(GlobEngine.GetGameScreen());
		GlobEngine.ResetScreen((int)event.resize.w,(int)event.resize.h);
	}

	if(event.key.keysym.sym == SDLK_LEFTBRACKET)
	{
		GraphicsM.Fade_Out();
	}

	if(event.key.keysym.sym == SDLK_RIGHTBRACKET)
	{
		GraphicsM.Fade_In();
	}

	if(event.type == SDL_MOUSEBUTTONDOWN)
	{
		if(event.button.button == SDL_BUTTON_LEFT)
		{
			//All of the below is just for testing purposes

			//640 0.625
			//680 0.6640625
			//720 0.703125
			//800 0.78125
			//860 0.83984375
			//940 0.91796875
			//960 0.9375
			//1024 1.0
			//1160 1.1328125
			//1280 1.25
			//1440 1.40625
			//1660 1.62109375
			//GraphicsM.SetResRatio(680.0f);
		}
	}
}

void InputManager::Handle_Menu_Input()
{
	if(event.key.keysym.sym == SDLK_ESCAPE && Time <= SDL_GetTicks() + 5000)
	{
		Time = SDL_GetTicks();
	}

	if(event.key.keysym.sym == SDLK_w)
	{

		Menu->SelectUp();
		return;
	}

	if(event.key.keysym.sym == SDLK_s)
	{

		Menu->SelectDown();
		return;
	}

	if(event.key.keysym.sym == SDLK_RETURN)
	{
		Menu->Click();
		return;
	}

	
}
