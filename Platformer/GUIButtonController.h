#ifndef GBC_H
#define GBC_H
#include "GUIButton.h"

enum ControlType{
	CONTROL_HORIZONTAL,
	CONTROL_VERTICAL,
	CONTROL_NULL
};



class GUIButtonController : public GUIObject
{
	public:
		GUIButtonController();
		virtual void Handle();
		void LockPos(bool tr) {LockP = tr;}
		void SetControlType(int nt) {CtrlType = nt;}
		void AddButton(GUIButton* add) {GButtonV.push_back(add);}
	private:
		bool LockP;
		int CtrlType;
		std::vector<GUIButton*> GButtonV;

};
#endif