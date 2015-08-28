#include "Particle.h"
#include "Definitions.h"
#include "Engine.h"


Particle::Particle(double X, double Y)
{
	x = X;
	y = Y;
	life = 100;
	dead = false;
	

}

Particle::~Particle()
{

}

void Particle::Show()
{

	#ifdef _DEBUG
	//DevInfo("Head particle is at %f, %f...", x, y);
	#endif
}

bool Particle::is_dead()
{
	return life <= 0;
}

void Particle::deltaPosition(double deltaX, double deltaY)
{
	x += deltaX;
	y += deltaY;
	cout << Solidity << endl;
		
	DrawBox.x = (int)x;
	DrawBox.y = (int)y;

}

void Particle::update()
{
	SetSolidity(TYPE_SOLID);
	life--;
}