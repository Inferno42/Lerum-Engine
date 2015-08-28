#include "AClock.h"

AClock* Enviroment = new AClock();

AClock::AClock()
{

}

int AClock::GetTimeHours()
{
	PullTime();
	return (int)(Hours + (Minutes / 60) + ((Seconds / 60) / 60));
}

int AClock::GetTimeMilliseconds()
{
	PullTime();
	return (int)(((Hours * 60) * 60) * 1000) + ((Minutes * 60) * 1000) + (Seconds * 1000);
}

int AClock::GetTimeMinutes()
{
	PullTime();
	return (int)(Hours * 60) + Minutes + (Seconds / 60);
}

int AClock::GetTimeSeconds()
{
	PullTime();
	return (int)((Hours * 60) * 60) + (Minutes * 60) + Seconds;
}

int AClock::GetDay()
{
	return Day;
}

char* AClock::GetMonth()
{
	return Month;
}

int AClock::GetYear()
{
	return Year;
}

void AClock::PullTime()
{
	_time = time(NULL);
	char* nCount = ctime(&_time);

	char* vars[7];

	int i = 0;
	char * pch = strtok(nCount," :");
	while ( pch != NULL)
	{
		vars[i] = pch;
		++i;
		pch = strtok(NULL," :");
	}
	Month = vars[1];
	Day = atoi(vars[2]);
	Hours = atoi(vars[3]);
	Minutes = atoi(vars[4]);
	Seconds = atoi(vars[5]);
	Year = atoi(vars[6]);
	
}
