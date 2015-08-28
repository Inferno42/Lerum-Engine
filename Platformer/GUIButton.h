#ifndef GBUTTON_H
#define GBUTTON_H
#include "GUIObject.h"
#include "GUIText.h"

//GUIButton works by hooking the function it needs and calling it when pressed.
class GUIButton : public GUIObject
{
	public:
		GUIButton();
		void HookFunction(void* func);
		void CallFunction();
		void Press();
		void SetButtonText( char* _text, int size, std::string iden);
		virtual void Handle();
		void SetColor(float R, float G, float B, std::string iden);

	private:
		GUIText tx;
		SDL_Event* even;
		void* bFunc; //Function to hook
};
#endif //GBUTTON_H