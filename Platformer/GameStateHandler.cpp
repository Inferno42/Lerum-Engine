#include "GameStateHandler.h"

GameStateHandler::GameStateHandler()
{
	currentstate = STATE_ACTIVE;
}

void GameStateHandler::SetGameState(int state)
{
	currentstate = state;
}

void GameStateHandler::ToggleState()
{
	if(currentstate == STATE_ACTIVE)
	{
		currentstate = STATE_MENU;
	}
	if(currentstate == STATE_MENU)
	{
		currentstate = STATE_ACTIVE;
	}
}