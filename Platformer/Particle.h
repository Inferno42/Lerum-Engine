#ifndef PARTICLE_H
#define PARTICLE_H

#include "Definitions.h"
#include "GraphicManager.h"

//This class may need to be re-worked, was hard coded to only create a particle explosion. -Inferno
class Particle : public CBaseEntity
{
	public:
		Particle(double X, double Y);
		~Particle();
		void Show();
		bool is_dead();
		void update();
	
		void setInitialDirection(double dir) { direction = dir; }
		double getDirection() { return direction; }
		void deltaPosition(double deltaX, double deltaY);
		void setInitialSpeed(double spd) { speed = spd; }
		double getSpeed() { return speed; }
	private:
		float x,y;
		int life;
		double speed;
		double direction;
};
#endif // PARTICLE_H