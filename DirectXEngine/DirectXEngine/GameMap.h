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

	// Function used to update the objects in map game. This is list objects with mission draw, update
	void Update(float dt);

	// Checking camera is in position left to with world map
	bool IsBoundLeft();
	// Checking camera is in position right to with world map
	bool IsBoundRight();
	// Checking camera is in position top world map
	bool IsBoundTop();
	// Checking camera is in position bottom world map
	bool IsBoundBottom();

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

