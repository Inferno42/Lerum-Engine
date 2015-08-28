#ifndef GAMESTATEHANDLER_H
#define GAMESTATEHANDLER_H

enum GameStates
{
	STATE_MENU,
	STATE_ACTIVE,
	STATE_PLAYERDEAD,
	STATE_CUTSCENE,
	STATE_UI
};

class GameStateHandler
{
	public:
		GameStateHandler();
		void SetGameState(int state);
		int GetCurrentState() {return currentstate;}
		void ToggleState();
	private:
	int currentstate;

};
#endif // GAMESTATEHANDLER_H