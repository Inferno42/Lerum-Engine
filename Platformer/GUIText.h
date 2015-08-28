#pragma once
#ifndef GTEXT_H
#define GTEXT_H

#include "GraphicManager.h"
#include "GUIObject.h"

#define GUIText_Expiration 9999999999999999
#define GUIText_Drawspeed 0 //0 Being the fastest, this is the delay between tacking each letter.

//NOTE: GUIText is different than CSText (Cutscene Text).
//Although they are both technically GUIObjects, CSText will have speed
//while GUIText has instant speed & no cutoff time.
//As a Text based object, this does not need to be added to the entity list.
//When the TextHandler has Handle() called, the text entities will be called as well.
class GUIText : public GUIObject
{
	public:
		GUIText();

		//Forces the text to be killed, this is used during deconstruction of GUIs.
		//Since it isn't handled by the Entity handler, it must be killed in the Text Handler.
		void Kill(); 

		void Draw();
		void SetText( char* _text, int X, int Y, int _size, char* fntn );
		Text* GetText() {return mText;}
		void ChangeText(char* _text);
	private:
		Text* mText;

};
#endif