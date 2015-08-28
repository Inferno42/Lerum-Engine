#ifndef ACLOCK_H
#define ACLOCK_H
#include <time.h>
#include <iostream>

#define SECONDS_24_HOURS 86400 //Night
#define SECONDS_12_HOURS SECONDS_24_HOURS / 2 //Midday

class AClock
{
	public:
		AClock();
		int GetTimeMilliseconds();
		int GetTimeSeconds();
		int GetTimeMinutes();
		int GetTimeHours();
		int GetDay();
		int GetYear();
		char* GetMonth();
		void PullTime();

	private:
		time_t _time;

		char* Month;
		int Year;
		int Seconds;
		int Minutes;
		int Hours;
		int MS;
		int Day;
}; extern AClock* Enviroment;


#endif //ACLOCK_H