#pragma once
#ifndef MENU_H
#define MENU_H
#include "Definitions.h"
#include "BaseClass.h"
#include "GUIButtonController.h"
#include "GUIMaster.h"

enum Modes{
	MODE_MENU,
	MODE_SAVE,
	MODE_LOAD,
	MODE_OPTIONS
};

class CMenu : public GUIMaster
{
	public:
		CMenu();
		~CMenu();

		void Setup();
		virtual void Handle();
		void SetVis();
		void SetInvis();
		void SelectUp();
		void SelectDown();
		void Click();
		void Load_Items();
		bool Visible;

	private:
		
		int SelectedItem;
		int Mode;
		GUIButtonController *cntrl;
		GUIButton* bInventory;
		GUIButton* bCompanions;
		GUIButton* bMap;
		GUIButton* bOptions;
		
}; extern CMenu* Menu;

#endif // MENU_H