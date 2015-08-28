#include "GUIText.h"

GUIText::GUIText()
{
	mText = new Text();
	mText->ForceKill = false;
	mText->setspeed(GUIText_Drawspeed); //This will instantly draw any text.
	mText->setholdtime(GUIText_Expiration); //Never expire. The text must be killed manually.
}

void GUIText::SetText( char* _text, int X, int Y, int _size, char* fntn )
{
	mText->set( _text, X, Y, _size, fntn );
}

void GUIText::ChangeText(char* _text)
{
	mText->Catstring[0] = _text; //Albeit slightly inefficient, GUIText should NEVER use \n.
}

void GUIText::Kill()
{
	mText->ForceKill = true;
	mText->Done_Printing = true;
}

void GUIText::Draw()
{
	//GraphicsM.ParseText(mText);
}

