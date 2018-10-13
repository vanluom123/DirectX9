#ifndef __GAME_MAP__
#define __GAME_MAP__

#include "Sprite.h"
#include "../DirectXEngine/MapReader/Tmx.h.in"
#include "GameGlobal.h"
#include "Camera.h"
#include "Brick.h"

class GameMap
{
public:
	explicit GameMap(const char* filePath);

	Tmx::Map* GetMap();

	int GetWidth();
	int GetHeight();
	int GetTileWidth();
	int GetTileHeight();

	void SetCamera(Camera *camera);

	void Draw();

	//Dung de update cac object trong map, nam cac list object nhan nhiem vu ve va update cho chung
	void Update(float dt);

	bool IsBoundLeft();			// kiem tra luc nay Camera o vi bien ben trai so voi WorldMap
	bool IsBoundRight();		// kiem tra xem co o vi tri bien ben phai worldmap khong
	bool IsBoundTop();			// kiem tra xem co o vi tri bien ben trai worldmap khong
	bool IsBoundBottom();		// kiem tra xem co o vi tri bien ben phai worldmap khong

	RECT GetWorldMapBound();

	~GameMap();

private:
	void LoadMap(const char* filePath);

	static bool isContain(RECT rect1, RECT rect2);

	Tmx::Map                        *mMap;

	std::map<int, Sprite*>          mListTilesSet;

	Camera*							mCamera;

	std::vector<Brick*>				mListBricks;

};
#endif

