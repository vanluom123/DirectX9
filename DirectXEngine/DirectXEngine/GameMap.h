#pragma once
#ifndef __GAME_MAP__
#define __GAME_MAP__

#include <d3dx9.h>
#include <d3d9.h>
#include <vector>

#include "Sprite.h"
#include "../DirectXEngine/MapReader/Tmx.h.in"
#include "GameGlobal.h"
#include "Camera.h"

class GameMap
{
public:
	GameMap(const char* filePath);

	Tmx::Map* GetMap() const;

	int GetWidth() const;
	int GetHeight() const;
	int GetTileWidth() const;
	int GetTileHeight() const;

	void SetCamera(Camera *camera);

	void Draw();

	~GameMap();

private:
	void LoadMap(const char* filePath);

	static bool isContain(RECT rect1, RECT rect2);

	Tmx::Map                        *mMap{};
	std::map<int, Sprite*>          mListTileset;
	Camera *mCamera{};
};

#endif

