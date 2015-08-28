#ifndef TILE_MANAGER_H
#define TILE_MANAGER_H
#include "Tile.h"
#include "File.h"
#include "DaemonClass.h"

struct TileSetting
{
	std::string parentsheet;
	int cropx, cropy, cropw, croph, vsolid;
};

typedef std::map<std::string, TileSetting> TMapDef;



class CTileManager : public CDaemonEntity
{
	public:
		CTileManager();
		~CTileManager();

		void Precache_Tiles();
		void Load_Tiles(std::string level);
		virtual void Handle();

	private:
		CFile Settings_File;
		CFile Level_File;
		CFile Order_File;
		string levels_dir;
		TMapDef TMap; //Tile Map;
};

#endif // TILE_MANAGER_H