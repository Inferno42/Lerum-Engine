#pragma once
#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H
#include "DaemonClass.h"
#include "Sound.h"


class CSoundManager : public CDaemonEntity
{
	public:
		CSoundManager();
		void Add_To_Queue(CSound base);
		void Handle_Queue();
	private:
	std::stack<CSound> Queue;
};

#endif // SOUNDMANAGER_H