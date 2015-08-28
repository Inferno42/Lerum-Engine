#pragma once
#ifndef MENUITEM_H
#define MENUITEM_H
#include "Definitions.h"
#include "TextHandler.h"

class CMenuItem : public CBaseEntity
{
	public:
		CMenuItem();
		~CMenuItem();

		void Handle();
		void Highlight();
		void Deselect();
		void SetText(string txt);
		void SetPos(int X, int Y);
	
	private:
		CTextHandler FMan;

};
#endif // MENUITEM_H