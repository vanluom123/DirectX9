#ifndef __GAME_MAP__
#define __GAME_MAP__

#include "Sprite.h"
#include "../DirectXEngine/MapReader/Tmx.h.in"
#include "GameGlobal.h"
#include "Camera.h"

class GameMap
{
public:
	GameMap(const char* filePath);

	Tmx::Map* GetMap();

	int GetWidth();
	int GetHeight();
	int GetTileWidth();
	int GetTileHeight();

	void SetCamera(Camera *camera);

	void Draw();

	~GameMap();

private:
	void LoadMap(const char* filePath);

	static bool isContain(RECT rect1, RECT rect2);

	Tmx::Map                        *mMap;
	std::map<int, Sprite*>          mListTilesSet;

	Camera* mCamera;

};
#endif

