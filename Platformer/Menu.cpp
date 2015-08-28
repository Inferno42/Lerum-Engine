#include "Menu.h"
#include "GraphicManager.h"
#include "Engine.h"

CMenu* Menu = new CMenu();

CMenu::CMenu()
{

}

CMenu::~CMenu()
{

}

void CMenu::Handle()
{
	
	if(Visible == true)
	{
		BASE::Handle();
		cntrl->Handle();
		if(Mode == MODE_MENU)
		{
			
		}
	}
	else
	{
		//Do nothing
	}

	
}

void CMenu::SelectUp()
{
	if(SelectedItem == 0)
	{
		SelectedItem = 6;
		return;
	}
	else
	{
		++SelectedItem;
		return;
	}
}

void CMenu::SelectDown()
{
	if(SelectedItem == 6)
	{
		SelectedItem = 0;
		return;
	}
	else
	{
		--SelectedItem;
		return;
	}
}

void CMenu::Click()
{
	if(Mode == MODE_MENU)
	{
		switch(SelectedItem)
		{
			case 0:
				SetInvis();

			case 4:
				SDL_Quit();
				exit(0);
		}
	}
}

void CMenu::Load_Items()
{

}

void CMenu::Setup()
{
	dead = false;
	Visible = false;
	Mode = MODE_MENU;
	Exemp = VIEW_EXEMPT;

	Crops[0].x = 133;
	Crops[0].y = 55;
	Crops[0].w = 254;
	Crops[0].h = 394;

	DrawBox.x = 000;
	DrawBox.y = 600;
	DrawBox.w = 254;
	DrawBox.h = 394;
	CurrentCrop = 0;

	Load_Items();
	Sprite = GraphicsM.Get_SpriteSheet(2).m_Sheet;
	SheetSize = GraphicsM.Get_SpriteSheet(2).size;

	cntrl = new GUIButtonController();
	bInventory = new GUIButton();
	bCompanions = new GUIButton();
	//bMap = new GUIButton();
	//bOptions = new GUIButton();
	bInventory->SetOffset(0, 100);
	cntrl->AddButton(bInventory);
	cntrl->AddButton(bCompanions);
	//cntrl->AddButton(bMap);
	//cntrl->AddButton(bOptions);
	bInventory->SetButtonText("Inventory", 24, "Inventory");
	bInventory->SetColor(0.5,-1.0,-1.0,"Inventory");
	bCompanions->SetButtonText("Companions", 24, "Companions");
//	bMap->SetButtonText("Map", 24);
//	bOptions->SetButtonText("Options", 24);
	cntrl->LockPos(true);
	cntrl->SetControlType(CONTROL_HORIZONTAL);


	ENT_INCREMENT(this);
}

void CMenu::SetVis()
{
	Visible = true;
}

void CMenu::SetInvis()
{
	Visible = false;
}
