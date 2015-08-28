#ifndef TIMER_H
#define TIMER_H
#include "Definitions.h"

class Timer
{
public:
	Timer();
	void start();
	void stop();
	int get_ticks();
	void pause();
	void unpause();
	bool is_started();
	bool is_paused();

private:
	int startTicks;
	int pausedTicks;
	bool paused;
	bool started;
};
#endif // TIMER_H