#include "SoundManager.h"

CSoundManager::CSoundManager()
{

};

void CSoundManager::Add_To_Queue(CSound base)
{
	Queue.push(base);
}

void CSoundManager::Handle_Queue()
{
	while(!Queue.empty())
	{
		CSound sound = Queue.top();
		if(sound.GetSound() != NULL)
			sound.Play();
		Queue.pop();
	}
}
