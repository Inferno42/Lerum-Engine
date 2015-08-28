#pragma once
#ifndef DEF_H
#define DEF_H
#include <iostream>
#include <vector>
#include "glew/include/GL/glew.h"
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include "SDL_collide.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include <conio.h>
#include <Windows.h>
#include "GameStateHandler.h"
#include <math.h>
#include <sstream>
#include <fstream>
#include <time.h>
#include <map>

extern "C" { extern FILE _iob[3];}
#include "glp/glpng.h"
#include <cmath>

#define pi 3.1415826535897932

#define _clrint -17891602 //default integer becomes this if uninitialized.

#define MaxTransparency 0.5

extern GameStateHandler GameStateH;

using std::vector;
using std::map;
#define cout std::cout
#define cerr std::cerr
#define endl std::endl
#define svector std::vector //Renamed from just vector due to ftgl issues. svector is really only used in CTextHandler.
using std::string;

//#ifdef _DEBUG
	#pragma warning( disable : 4244 4305 4018 4615 4996;) // :(100): Used to clean up compiler log. MUST BE REMOVED EVENTUALLY.
//#endif // _DEBUG

//Note: :(100): is to be added at the end of function declarations that need to be removed later.
//Adding this to the end makes it so much easier to track them down among all the other functions.
//Simply do Ctrl+F and then type the code and hunt down functions or members, etc.

//Note: :(200): is to added when a function, file, etc needs attention. Usually a future change or such.



float DistanceFrom(float ax, float ay, float bx, float by);

/*
*Gives a direction in simple number form
* 0 W 
* 1 NW 
* 2 N 
* 3 NE 
* 4 E 
* 5 SE 
* 6 S 
* 7 SW
*/
int DirectionTo(int ax, int ay, int bx, int by); 


#ifdef _DEBUG
//#define _DevError(msg); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12); cerr << "[ERROR] " << msg << endl; SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
#define _DevErrorInfo(); cerr << endl << "\tLine: " << __LINE__ << endl << "\tTime: " << __TIMESTAMP__ << endl << "\tFile: " << __FILE__ << endl; SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
#define _DevError(msg); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12); cerr << "[ERROR] " << msg << endl; SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
#define _DevInfo(msg); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15); cout << "[INFO] " << msg << endl;
#define _DevDrop(msg); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11); cout << "[-DEV] " << msg << endl; SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
void DevError(string format, ...); //Writes an error message to the console [ERROR]
void DevInfo(string format, ...); //Writes an info message to the console [INFO]
void DevDrop(string format, ...); //Writes a dropdown message to the console, used to continue info messages [----]
#endif



#ifdef _DEBUG
#define INIT_SDL(); if(SDL_Init(SDL_INIT_EVERYTHING) != 0) { DevError("Error initalizing SDL!");} if(TTF_Init() != 0) { DevError("Error initializing SDL_TTF!"); } SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15); DevInfo("Debug mode detected."); 
#else
#define INIT_SDL(); if(SDL_Init(SDL_INIT_EVERYTHING) != 0) { cerr << "Error initalizing SDL!";} if(TTF_Init() != 0) { cerr << "Error initializing SDL_TTF!"; } 
#endif // _RELEASE

struct GLRect{
	GLfloat x;
	GLfloat y;
	GLfloat w;
	GLfloat h;
};

struct Sheet
{
	int size;
	GLuint m_Sheet;
};

struct float3
{
	float X;
	float Y;
	float Z;
};

struct float2
{
	float X;
	float Y;
};


#endif // DEF_H