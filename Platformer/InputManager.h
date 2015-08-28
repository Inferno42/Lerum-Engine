#ifndef INPUTCORE_H
#define INPUTCORE_H
#include "Definitions.h"
#include "GraphicManager.h"

class InputManager
{
	public:
		InputManager();
		void Handle_Player_Input();
		void Handle_Menu_Input();
		void Handle_DEBUG(); // Used for testing
		void HandleInput();
	private:
	SDL_Event event;
	float Time;
	CShader* ns;
};

#endif //INPUTCORE_H