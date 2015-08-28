#include "GUIButton.h"
#include "Camera.h"

GUIButton::GUIButton()
{
	PRECACHE_TEXTURE("Data\\ButtonTest.png","ButtonTest",200);
	Sprite = LOAD_TEXTURE("ButtonTest").m_Sheet;
	SheetSize = LOAD_TEXTURE("ButtonTest").size;
	Exemp = VIEW_EXEMPT;
	DrawBox.x = 0;
	DrawBox.y = 0;
	DrawBox.w = 200;
	DrawBox.h = 75;
	customheight = true;


	CurrentCrop = 0;
	Crops[0].x = 0;
	Crops[0].y = 0;
	Crops[0].w = 200;
	Crops[0].h = 75;
	SizeRatio = 1.0f;

	//SetOffset(100,100);
}

void GUIButton::CallFunction()
{
	 if(bFunc)
	 {
		 reinterpret_cast< void( * ) () > (bFunc) ();
	 }
}

void GUIButton::HookFunction( void* func )
{
	bFunc = func;
}

void GUIButton::Press()
{
	CallFunction();
}

void GUIButton::SetColor(float R, float G, float B, std::string iden)
{
	GraphicsM.TxHan.ChangeColor(R,G,B,iden);

}
void GUIButton::SetButtonText( char* _text, int size, std::string iden)
{
	//Draw Vectors
	const float dv_s = size;// / (GetDrawBox().w * GetDrawBox().h / 10);
	X_Button = gCam.GetCamera().x + GetXOffset();
	Y_Button = (gCam.GetCamera().h - GetYOffset()); //Translate inversed FTGL coords into standard coords
	Y_Button -= (GetDrawBox().h / 2);
	X_Button += (GetDrawBox().w / 4);
	char* dv_fn = "Data\\IrishUncialfabeta-Bold.ttf";
	
	tx.SetText(_text, X_Button, Y_Button, dv_s, dv_fn);
	GraphicsM.ParseText(tx.GetText(), iden);
}

void GUIButton::Handle()
{
//	bool leftB;
	even = NULL;

	const float dv_x = gCam.GetCamera().x + GetXOffset();
	const float dv_y = gCam.GetCamera().y + GetYOffset();

	this->SetPos(dv_x , dv_y);

	
	BASE::Handle();
}
