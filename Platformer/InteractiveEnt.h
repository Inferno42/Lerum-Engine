#pragma once
#ifndef INTERACTIVEENT_H
#define INTERACTIVEENT_H
#include "BaseClass.h"

//This class will be what objects such as doors, buttons, switches, and others will inherit from.
class CInteractiveEntity : public CBaseEntity
{
	public:
		CInteractiveEntity();
		virtual void Spawn(int X, int Y);
		virtual void Press();
		virtual void Handle();
		virtual void Hover();
		
	
	private:
		SDL_Event event;
		

};
#endif