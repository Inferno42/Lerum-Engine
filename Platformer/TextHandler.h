#pragma once
#ifndef FONTMAN_H
#define FONTMAN_H

#define SC_SPEED 100 //Delay between each letter being placed.
#define SC_HOLDTIME 800  //Time after display if finished before it should go away.

#include "Definitions.h"
#include "DaemonClass.h"

#include <ftglm/src/FTGL/ftgl.h>
#include <ftglm/src/FTGL/FTGLTextureFont.h>
#include <ftglm/src/FTGL/FTPoint.h>

//Text: Basic structure that allows easy sorting of text to be displayed.
class Text{
	
	public:
	Text();

	vector<string> Catstring; //Parsed sentences are letter by letter concatregated to this char*.
	char* ToParse;
	void set(char* _text, int X, int Y, int _size, char* fntn);
	void parse(char* _p);
	void setspeed(int _s);
	void setholdtime(int _s);

	void tack(); // This function should NEVER be called manually. Only to be used by the FontManager. - Inferno

	int SelectionTack; // Which element string in Catstring to start tacking. Used to display and tack. - Inferno

	bool Done_Printing;

	unsigned int SC_OVERRIDE;
	vector<FTPoint> pos;
	int sizeholder;
	int sumsize;
	int defX;
	int defY;
	vector<vector<char>> parsed;
	FTGLPixmapFont* fnt;
	int size;
	vector<unsigned> curnum;
	int spd;
	int LastTickCheck;
	bool ContainsDrop;
	bool ForceKill;
	bool CustomHold;
	int HoldTime;
	float3 color;
};

typedef std::map<std::string, Text*> txtmap;

class CTextHandler : public CDaemonEntity
{
	public:
		CTextHandler();
		virtual void Handle();
		void ParseString(Text* text, std::string identifier);
		void SetVis() {Visible = true;}
		void SetInVis() {Visible = false;}

	public: //Text Modifiers
		void ChangeColor(float R, float G, float B, std::string iden) 
		{
			TextVector[iden]->color.X = R;
			TextVector[iden]->color.Y = G;
			TextVector[iden]->color.Z = B;
		};
		txtmap PullMapInfo() {return TextVector;}
	private:
		SDL_Surface* tmphldr;
		bool Visible;
		SDL_Color col;
		txtmap TextVector;
		int counter;

};

//TEXTCOLOR DOC
//I have yet to figure out a way around this, ftgl is absurdly picky.
//255 = 1.0f
//127.5 = 0.0f
//0 = -1.0f
#define TEXTCOLOR(r,g,b) glPixelTransferf(GL_RED_BIAS, r); glPixelTransferf(GL_GREEN_BIAS, g); glPixelTransferf(GL_BLUE_BIAS, b);


#endif // FONTMAN_H