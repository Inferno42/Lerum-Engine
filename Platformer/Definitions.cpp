#include "Definitions.h"
#include "Camera.h"
#include <string.h>

CCamera gCam;
GameStateHandler GameStateH;

extern "C" { FILE _iob[3] = {__iob_func()[0], __iob_func()[1], __iob_func()[2]}; }


float DistanceFrom(float ax, float ay, float bx, float by)
{

	return sqrt(pow((bx - ax),2) + pow((by - ay),2));
}


int DirectionTo(int ax, int ay, int bx, int by)
{
	if(ay > by && ax < bx)
	{
		return 3;
	}

	if(ay > by && ax > bx)
	{
		return 1;
	}

	if(ay < by && ax < bx)
	{
		return 5;
	}

	if(ay < by && ax > bx)
	{
		return 7;
	}

	if(ay < by)
	{
		return 6;
	}

	if(ay > by)
	{
		return 2;
	}

	if(ax < bx)
	{
		return 4;
	}

	if(ax > bx)
	{
		return 0;
	}
	return -1; //Something strange happened, where is the entity?! He wasn't found in any direction! 
	//Second note: -1 can also mean that the npc is directly on top of what ever it is looking for. - Inferno
}

#ifdef _DEBUG

void DevError(string format, ...)
{
	va_list args;
	char    buffer[512] = {0};

	va_start(args, format);
	vsnprintf(buffer, sizeof(buffer), format.c_str(), args);
	va_end(args);

	strncat(buffer, "\r", (sizeof(buffer) - strlen(buffer)));
	_DevError(buffer);
}

void DevInfo(string format, ...)
{
	va_list args;
	char    buffer[512] = {0};

	va_start(args, format);
	vsnprintf(buffer, sizeof(buffer), format.c_str(), args);
	va_end(args);

	strncat(buffer, "\r", (sizeof(buffer) - strlen(buffer)));
	_DevInfo(buffer);
}

void DevDrop(string format, ...)
{
	va_list args;
	char    buffer[512] = {0};

	va_start(args, format);
	vsnprintf(buffer, sizeof(buffer), format.c_str(), args);
	va_end(args);

	strncat(buffer, "\r", (sizeof(buffer) - strlen(buffer)));
	_DevDrop(buffer);
}

#endif // DEBUG