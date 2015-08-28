#include "Sound.h"

void CSound::Play()
{
	Mix_PlayChannel(-1, sound, 0);
}

void CSound::Pause()
{
	Mix_Pause(-1);
}

void CSound::Load_Wav( const char * filename )
{
	this->sound = Mix_LoadWAV(filename);
	if(sound == NULL)
	{
		#ifdef _DEBUG
		DevError("%s",SDL_GetError());
		#endif
	}
}

void CSound::Volume( int vol )
{
	Mix_Volume(0,vol);
}
