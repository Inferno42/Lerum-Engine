#include "FPSCounter.h"

void FPSCounter::Tick()
{
	++frames;

	last = newtick;

	newtick = SDL_GetTicks();

	accdelay += newtick - last;

	if(accdelay > 1000) //1 second
	{
		fps = frames;
		StartCounter();
	}


}

void FPSCounter::StartCounter()
{
	frames = 0;
	accdelay = 0;
}
