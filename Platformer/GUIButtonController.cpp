#include "GUIButtonController.h"
#include "Engine.h"

GUIButtonController::GUIButtonController()
{
	CtrlType = 0;
	LockP = false;
}

void GUIButtonController::Handle()
{
	if(LockP)
	{
		if(CtrlType == CONTROL_HORIZONTAL)
		{
			for(int i = 1; i <= GButtonV.size() - 1; ++i)
			{
				
				GButtonV[i]->SetOffset(GButtonV[i-1]->GetXOffset() + 300, GButtonV[i-1]->GetYOffset());
				//GButtonV[1]->SetOffset(0,300);
			}
		}
		if(CtrlType == CONTROL_VERTICAL)
		{
			for(int i = 1; i <= GButtonV.size() - 1; ++i)
			{
				GButtonV[i]->SetPos(GButtonV[0]->GetXOffset(), GButtonV[i-1]->GetYOffset() - 300);
			}
		}
	}

	HandleChildren(GButtonV);
}