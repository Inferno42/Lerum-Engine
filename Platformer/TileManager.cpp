#include "TileManager.h"
#include "Engine.h"

CTileManager::CTileManager()
{
	Settings_File.Open("Data\\Scripts\\TILE_SETTINGS.ini");
	levels_dir = "Data\\Levels\\";
}

CTileManager::~CTileManager()
{

}

void CTileManager::Load_Tiles(std::string level)
{
	string tmp2;

		Level_File.Open(levels_dir + level.c_str() + ".dat");

		while(getline(Level_File.File,tmp2))
		{
			std::istringstream parser1(tmp2, std::istringstream::in);
			string Varname;
			int x,y;

			parser1 >> Varname >> x >> y;
			
			TileSetting tile = TMap[Varname];

			CTile *_t = new CTile();

			//int sheet = atoi(sheetbuf.c_str());

			SDL_Rect _tmprect = {x, y, tile.cropw, tile.croph};
			SDL_Rect _tt = {tile.cropx, tile.cropy, tile.cropw, tile.croph};
			_t->Crops[0] = _tt;

			Sheet tmpsht = LOAD_TEXTURE(tile.parentsheet);

			_t->SetDrawBox(_tmprect);
			_t->SetSheetSize(tmpsht.size);
			_t->Set_Crop(0);
			_t->SetSprite(tmpsht.m_Sheet);
			_t->SetSolidity(tile.vsolid);
			_t->Spawn();
			
		}
	
}

void CTileManager::Handle()
{

}

void CTileManager::Precache_Tiles()
{
	string tmp3;

	while(getline(Settings_File.File, tmp3))
	{
		std::istringstream settingparser(tmp3, std::istringstream::in);
		TileSetting tile;
		std::string id;
		settingparser >> id;

		if((strcmp(id.c_str(),"//") == 1) && (strcmp(id.c_str(),"") == 1)) //If the line is not a comment.
		{
			settingparser >> tile.parentsheet >> tile.cropx >> tile.cropy >> tile.cropw >> tile.croph >> tile.vsolid;
			TMap[id] = tile;
		}
	}
}
