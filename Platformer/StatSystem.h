#ifndef STATSYS_H
#define STATSYS_H

enum Weapon_Grade
{
	Super_Heavy,
	Heavy,
	Medium,
	Light,
	Super_Light
};

class CStatSystem
{
public:
	void ResetAll() {voidstat = 5; strengthstat = 5; endurancestat = 5; dexteritystat = 5; intelligencestat = 5; level = 1;};

	double CalculateHealth(int health);
	double CalculateArmor(int armorrating);
	double CalculatePhysicalDamage(int BaseDamage, int WeaponGrade);

private:
	int level;
	int voidstat;
	int strengthstat;
	int endurancestat;
	int dexteritystat;
	int intelligencestat;

};

#endif // STATSYS_H