#pragma once
#ifndef GRAPHICS_CORE_H
#define GRAPHICS_CORE_H
#include "Definitions.h"
#include "BaseClass.h"
#include "Timer.h"
#include <stack>
#include "TextHandler.h"
#include "ShaderController.h"

typedef std::map<std::string, Sheet> Gmap;


extern Gmap Gmaps;

const int FPS = 20; // 60 FPS

class GraphicsCore
{
	public:
		GraphicsCore();
		//void Draw(SDL_Rect, GLuint, GLRect, int, GLfloat, GLfloat, GLfloat, int, bool);
		void Draw(CBaseEntity*);
		GLuint Load_Image(string);
		void Add_To_Draw_Queue(CBaseEntity*);
		void Handle_Queue();
		Sheet Get_SpriteSheet(int);
		void Precache_Sheets();
		void Maintain_Framerate();
		void Fade_In();
		void Fade_Out();
		void Fade_In_Death();
		void Handle_Aux();
		void Stop_Fade();
		void Setup_TxHan();

		bool GetFading() {return Fade_Active;}

		void ParseText(Text* text, std::string iden) {TxHan.ParseString(text, iden);}

		double GetResRatio() {return ResRatio;}
		void SetResRatio(double rra) {ResRatio = rra / 1024;}

		void SetupFBO();

		std::stack<CBaseEntity*> DrawQueue;

		CTextHandler TxHan;

		CShaderController ShaderController;
private:
		GLuint vbo;

		int frame;
		Timer fps;
		Timer update;

		Sheet Precached_Sheets[20];
		double ResRatio;

		bool Fade_Active;
		int Fading; // 0 Fading in; 1 Fading out
		GLfloat Perc;
		GLfloat Perc2;
};

extern GraphicsCore GraphicsM;


#define PRECACHE_TEXTURE(txloc, txname, txsize) if(Gmaps.find(txname) == Gmaps.end()) {Sheet tmp; tmp.m_Sheet = GraphicsM.Load_Image(txloc); tmp.size = txsize; Gmaps[txname] = tmp; /*DevInfo("%s precached successfully!",txname);*/} else{/*DevError("%s is already precached.", txname);*/}
Sheet LOAD_TEXTURE(std::string txname);

#endif // GRAPHICS_CORE_H