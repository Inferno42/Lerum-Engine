#include "StatSystem.h"
#include "Definitions.h"


double CStatSystem::CalculateHealth( int health )
{
	return 100 * (endurancestat / 4);
}

double CStatSystem::CalculateArmor( int armorrating )
{
	return 100 * (armorrating / 24);
}

double CStatSystem::CalculatePhysicalDamage( int BaseDamage, int WeaponGrade )
{
 //The reasoning behind this magic seed is so its 
	//1:Non Windows proprietary
	//2:Still Pseudo-Random
	//All the stats being added below change so often that it makes it hard for
	//us to have recursive numbers and same seeds.
	srand((BaseDamage * WeaponGrade + strengthstat + voidstat + dexteritystat) / pi);
	int max, min, var, damage;
	switch(WeaponGrade)
	{
		case Super_Heavy:
			 max = BaseDamage * (strengthstat / 1.6);
			 min = max * 0.4;
			 var = rand() % max - min;

			 damage = var * (strengthstat / 1.6);
			return damage;
		case Heavy:
			 max = BaseDamage * (strengthstat / 2);
			 min = max * 0.4;
			 var = rand() % max - min;

			 damage = var * (strengthstat / 2);
			return damage;
		case Medium:
			 max = BaseDamage * ((strengthstat / 6) + (dexteritystat / 6));
			 min = max * 0.4;
			 var = rand() % max - min;

			 damage = var * ((strengthstat / 6) + (dexteritystat / 6));
			return damage;
		case Light:
			 max = BaseDamage * (dexteritystat / 4);
			 min = max * 0.4;
			 var = rand() % max - min;

			 damage = var * (dexteritystat / 4);
			return damage;
		case Super_Light:
			 max = BaseDamage * (dexteritystat / 8);
			 min = max * 0.4;
			 var = rand() % max - min;

			 damage = var * (dexteritystat / 8);
			return damage;
	}
}
