#ifndef PARTICLEMANAGER_H
#define PARTICLEMANAGER_H
#include "Particle.h"
#include "DaemonClass.h"

//ParticleManager needs to be filled out. I may end up doing this in the next revision. -Inferno.

class ParticleManager : public CDaemonEntity
{
public:
	static const int PLAIN_FIREWORKS = 101;

	ParticleManager();
	ParticleManager(int X, int Y, int tp, Sheet sheet);
	~ParticleManager();
	void Set_Amount(int newam) {amount = newam;}
	void Set_Life(int newLI) {life = newLI;}


	void Generate_Particle(int x, int y);
	void Check_Particles();
	void Handle();
private:
	int x;
	int y;
	int type;
	int life;
	int amount;
	vector<Particle*> ActiveParticles;
	Sheet particleSheet;
};

#endif