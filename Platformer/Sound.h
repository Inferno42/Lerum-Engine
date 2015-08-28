#pragma once
#ifndef SOUND_H
#define SOUND_H

#include "Definitions.h"

class CSound
{
	public:
		CSound(const char * filename) {Load_Wav(filename);}
		CSound(string name) {Load_Wav(name.c_str());}
		void Play();
		void Pause();
		void Load_Wav(const char * filename);
		void Volume(int vol); // 0-128
		int GetVolume() {return Mix_VolumeChunk(sound,-1);}
		void FreeSound() {Mix_FreeChunk(sound);}
		Mix_Chunk* GetSound() {return sound; }

	private:
		Mix_Chunk* sound;
};
#endif // SOUND_H