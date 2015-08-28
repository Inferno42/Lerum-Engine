#include "TextHandler.h"
#include "Engine.h"
#include "Definitions.h"
#include "Camera.h"
#include <assert.h>

using std::vector;


CTextHandler::CTextHandler()
{
	dead = false;
	tmphldr = NULL;
	
	Depth = -0.1;
	CurrentCrop = 0;
	Crops[0].x = 0;
	Crops[0].y = 0;
	Crops[0].w = 0;
	Crops[0].h = 0;
	counter = 0;

}

void CTextHandler::Handle()
{

	if(Visible == true)
	{
		
		FTPoint spc = FTPoint();
		//glPixelTransferf(GL_RED_BIAS, -(col.r / 256));
		//glPixelTransferf(GL_GREEN_BIAS, -(col.g / 256));
		//glPixelTransferf(GL_BLUE_BIAS, -(col.b / 256));


		if(counter >= 20)
		{
			#ifdef _DEBUG
			DevError("Text handling counter over 20!!! Buffer overflow very likely!! Counter:%i SizeofTextVec:%i",
				counter, sizeof(TextVector));
			_DevErrorInfo();
			#endif
		}
		txtmap::const_iterator i, end(TextVector.end());

		for(i = TextVector.begin();
			i != TextVector.end();
			++i)
		{	
		
			Text* nt = i->second;
			if(nt->SC_OVERRIDE == true)
			{
				if(nt->spd + nt->LastTickCheck <= SDL_GetTicks() && nt->Done_Printing == false)
				{
					nt->tack(); //Tack on the next letter, number, space, what ever. -Inferno
				}
			}
			else
			{
				if(nt->LastTickCheck + SC_SPEED <= SDL_GetTicks() && nt->Done_Printing == false)
				{
					nt->tack();
				}
			}
				
			for(int a = 0; a <= nt->Catstring.size() - 1; a++)
			{
				float mult = (GlobEngine.GetGameScreen()->w * GlobEngine.GetGameScreen()->h);
				float delta = (mult / 480000);
				nt->fnt->FaceSize(nt->size * delta);
				TEXTCOLOR(nt->color.X, nt->color.Y, nt->color.Z)
				nt->fnt->Render(nt->Catstring[a].c_str(), -1, nt->pos[a], spc, 65535);
				
			}

			if(nt->CustomHold == false)
			{
				if((nt->Done_Printing == true && nt->LastTickCheck + SC_HOLDTIME <= SDL_GetTicks())
					|| nt->ForceKill == true)
				{
					TextVector.erase(i);
					--counter;
				}
			}
			else if((nt->Done_Printing == true && nt->LastTickCheck + nt->HoldTime <= SDL_GetTicks())
				|| nt->ForceKill == true)
			{
				TextVector.erase(i);
				--counter;
			}
		}
	}
}

void CTextHandler::ParseString( Text* text, std::string identifier )
{
	++counter;
	text->parse(text->ToParse);

	TextVector[identifier] = text;
}


void Text::parse( char* _p )
{

	char *fxv = new char();


	strcat(fxv, _p); //Copy input into a buffer.

	vector<char> parsedstring; //Used as buffer for splitting strings

	vector<char*> holder; //Holds fractured (Newline detected) strings so that they can be split into individual letters.

	char* pch; //MSDN: Splits string by \n newline

	int downcount = 0;

	pch = strtok(fxv,"\n");
	while ( pch != NULL)
	{
		++downcount;
		holder.push_back(pch);
		pch = strtok(NULL,"\n");
	}
	 //End MSDN



	// For every newline create another FTPoint (Coords for each text drop) and set it to be the original Y + size * Its number.
	if(downcount > 0)
	{
		ContainsDrop = true;
		for(int i = 1; i <= downcount; ++i) 
		{
			FTPoint _t;
			pos.push_back(_t);
		
		
	
			pos[i].X(defX);
			pos[i].Y((defY) - size * i);

			int b = 0;

			curnum.push_back(b);

			
		}
	}

	sumsize = 0;

	for(int a = 0; a <= downcount - 1; a++) // Scan through each of the stored newlines and spit them into letters
	{
		parsedstring.erase(parsedstring.begin(), parsedstring.end());
		for(int i = 0; i <= strlen(holder[a]); ++i)
		{
			parsedstring.push_back(holder[a][i]);
		
		}
		sumsize += parsedstring.size();
		parsed.push_back(parsedstring); // Push vector<char> (vector of the individual letters for 1 string) into a vector<vector<char>>. (Holds multiple split strings)
	}
//	DevInfo("Sum Size:%i", sumsize);
	sizeholder = parsed[0].size();


//	DevInfo("%i",sizeholder);

	//String is now split into one or multiple letters that form the original when put back together, they are stored under parsed[vector][letter] in that order.
}

void Text::set( char* _text, int X, int Y, int _size, char* fntn )
{
	ToParse = _text; // Set the text that will eventually be parsed.

	defX = X;
	defY = Y;
	pos[0].X(X);
	pos[0].Y(Y); //We only set the first element because all other elements will follow a formula based off the original.

#ifdef _DEBUG
	DevInfo("fontname:%s",fntn);
#endif

	fnt = new FTGLPixmapFont(fntn);
	if(fnt != NULL)
	{
		#ifdef _DEBUG
			DevInfo("Font successfully loaded!");
		#endif
	}
	else
	{
		#ifdef _DEBUG
			DevError("Font unable to be loaded.");
		#endif
	}

	size = _size; //Store it in the struct so that it can be accessed for the coords formula later.
	fnt->FaceSize(size);
}


void Text::tack()
{
	if(curnum[SelectionTack] == parsed[SelectionTack].size())
	{
		if(sizeholder >= sumsize)
		{
			Done_Printing = true;
			return; //We've hit the end of this text.
		}
		else
		{
			++SelectionTack;
			sizeholder += parsed[SelectionTack].size();
		//	DevInfo("%i",sizeholder);
		}
	}

		Catstring.erase(Catstring.begin(),Catstring.end()); //Clear the string in case it may have something in it. Usually left over from previous printing.

		for(int i = 0; i <= SelectionTack; ++i)
		{
			if(!parsed[SelectionTack][0])
			{
			//	DevError("Tack Selection:%i invalid!", SelectionTack);
			}
		}

		//Here we have 2 for loops working to tack on the correct string. It finds the selected string to start printing.
		//After selecting it builds the string from the ground up until it hits the maximum letter.
		//The max letter (curnum) is the letter that is being printed.
		//if curnum == the size of the selection then we have finished tacking onto the cat string.

		string buf;

		for(int a = 0; a <= SelectionTack; a++)
		{

			for(int i = 0; i <= curnum[a]; ++i)
			{
				if(i >= parsed[a].size() - 1 && a < SelectionTack)
				{
					++a;
					i = 0;
					Catstring.push_back(buf);
					buf.erase(buf.begin(), buf.end());
				}
				buf.push_back(parsed[a][i]);
			}

			Catstring.push_back(buf);
			buf.erase(buf.begin(), buf.end());
			++curnum[a];
		}

		LastTickCheck = SDL_GetTicks();
	
}

Text::Text()
{
	SC_OVERRIDE = false;
		spd = SC_SPEED;

	Done_Printing = false;

	LastTickCheck = 0;

	ContainsDrop = false;

	FTPoint tpos;

	pos.push_back(tpos); //So now we have a variable 0. -Inferno

	SelectionTack = 0;

}

void Text::setspeed( int _s )
{
	SC_OVERRIDE = true;
		spd = _s;
}

void Text::setholdtime( int _s )
{
	CustomHold = true;
		HoldTime = _s;
}
