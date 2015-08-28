#pragma once
#ifndef GOBJECT_H
#define GOBJECT_H

#include "BaseClass.h"

#define HandleChildren(x) for(int i = 0; i <= x.size() - 1; ++i) {x[i]->Handle();}


class GUIObject : public CBaseEntity
{
	public:
		GUIObject();
		virtual void Handle();
		virtual void SetOffset(float X, float Y) {X_Offset = X; Y_Offset = Y;}
		float GetXOffset() {return X_Offset;}
		float GetYOffset() {return Y_Offset;}
		

	protected:
		float X_Offset;
		float Y_Offset;
		float X_Button;
		float Y_Button;
};
#endif