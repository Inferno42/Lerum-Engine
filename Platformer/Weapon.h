#include "Item.h"

struct WBonuses
{
	int Int;
	int Str;
	int Dex;
	int Void;
	int Vit;
};

struct WStats : IStats
{
	string weight_cat;
	int BaseDamage;
};

struct DebugStats
{
	/*
	<item category="WEAPON">
		<id>0</id>
		<itemname>DEBUG WEAPON</itemname>
		<weightcategory>SUPER_HEAVY</weightcategory>
		<basedamage>360000</basedamage>
		<bonuses>
		<int>5</int>
		<strength>5</strength>
		</bonuses>
		</item>
		*/

	int id;
	const char* category;
	const char* itemname;
	const char* weightcategory;
	WBonuses bonuses;
};

class CWeapon : public CItem
{
	public:
		CWeapon() {};
		~CWeapon() {};

		virtual void Handle_Item_Effect();
		void LoadStats(int id);

	private:
		WBonuses bonuses;
		WStats stats;
};
