#include "BaseClass.h"
#include "GUIObject.h"

//GUIObjects are considered children to the Master, they will be handled WITH the master.
//They are handled in a vector along with being separate in order to create a simple handling balance.
//It create less cluttered code as well, when an individual object is needed it can be called directly.
//But when a child needs to be handled, it can wait until after the master is finished.
//This also ensures that children aren't handled if the parent is destroyed. Hence why the parent comes first. -Inferno
#define RegisterChild(x) children->push_back((GUIObject*)x); 

//This allows for modular design, instead of assuming you always want the vector named children, 
//you can use a different vector and still handle it the same way.
#define HandleChildren(x) for(int i = 0; i <= x.size() - 1; ++i) {x[i]->Handle();}


//The GUIMaster is used to create interfaces.
class GUIMaster : public CBaseEntity
{
	public:
		GUIMaster();
		virtual void Handle();

	protected:
		vector<GUIObject*> children;
};