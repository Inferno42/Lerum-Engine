#include "Menu_Item.h"
#include "Engine.h"

CMenuItem::CMenuItem()
{
//	FMan.SetFont_PXMap("Data\\marigoldwild.ttf");
//	FMan.SetColor(0,0,0);
}

CMenuItem::~CMenuItem()
{

}

void CMenuItem::Handle()
{
	BASE::Handle();
}

void CMenuItem::Highlight()
{
	//FMan.SetColor(255,0,0);
}

void CMenuItem::Deselect()
{
//	FMan.SetColor(0,0,0);
}

void CMenuItem::SetText(string txt)
{
//	FMan.SetText(txt);
}

void CMenuItem::SetPos(int X, int Y)
{
	//FMan.SetPos(X,Y);
}
