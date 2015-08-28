#ifndef FPS_H
#define FPS_H
#include "Definitions.h"

class FPSCounter
{
	public:
		FPSCounter() {last = 0; newtick = 0;}
		void StartCounter();
		void Tick();
		int GetFPS() {return fps;}

	private:
		int frames;
		double accdelay;
		double last;
		double newtick;
		int fps;

};



#endif //FPS_H