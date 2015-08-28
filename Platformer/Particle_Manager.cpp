#include "Particle_Manager.h"
#include "Engine.h"

ParticleManager::ParticleManager()
{
	type = PLAIN_FIREWORKS;
}

ParticleManager::ParticleManager(int X, int Y, int tp, Sheet sheet)
{
	x = X;
	y = Y;
	type = tp;
	particleSheet = sheet;
	dead = false;
	
}

ParticleManager::~ParticleManager()
{
	ActiveParticles.clear();
}

void ParticleManager::Generate_Particle(int x, int y)
{
	double direction = ((double)rand() / ((double)RAND_MAX + 1)) * 2.0 * pi;
	double speed = (double)rand() / ((double)RAND_MAX + 1);

	Particle* p = new Particle(x, y);
	p->SetSprite(particleSheet.m_Sheet);
	p->setInitialDirection(direction);
	p->setInitialSpeed(speed);
	p->Spawn(x, y);
	ActiveParticles.push_back(p);
}

void ParticleManager::Check_Particles()
{
	for(int i = ActiveParticles.size()-1; i > -1; i--)
	{
		if(ActiveParticles[i]->is_dead())
		{
			#ifdef _DEBUG
			//DevInfo("Removing dead particle at %i", i);
			#endif
				
			ActiveParticles[i]->Remove_Entity();
			ActiveParticles.erase(ActiveParticles.begin()+i);
		}
	}

	ActiveParticles.shrink_to_fit();
}

void ParticleManager::Handle()
{
	#ifdef _DEBUG
	//DevInfo("Handling %i particles", ActiveParticles.size());
	#endif

	for(int i = ActiveParticles.size()-1; i > -1; i--)
	{
		Particle* p = ActiveParticles[i];
		double deltaX = 1, deltaY = 0;

		switch(type)
		{
			case PLAIN_FIREWORKS:
			{
				deltaX = p->getSpeed() * cos(p->getDirection());
				deltaY = p->getSpeed() * sin(p->getDirection());
				break;
			}
		}

		p->deltaPosition(deltaX, deltaY);
		p->update();
	}

	if(ActiveParticles.size() > 0)
		ActiveParticles[0]->Show();
	else
		this->Remove_Entity();

	Check_Particles();
}