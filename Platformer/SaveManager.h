#include "Definitions.h"
#include "File.h"

class CSaveManager
{
	public:
		CSaveManager();
		~CSaveManager();

		void SaveGame(string SaveName);

	private:
		CFile SaveWriter;
};