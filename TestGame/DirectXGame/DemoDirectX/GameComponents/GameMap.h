#pragma once
#ifndef __GAME_MAP__
#define __GAME_MAP__

#include <d3dx9.h>
#include <d3d9.h>
#include <vector>

#include "../GameComponents/Sprite.h"
#include "../MapReader/Tmx.h.in"
#include "Camera.h"
#include "QuadTree.h"
#include "../GameObjects/MapObjects/Brick.h"

class GameMap
{
	void LoadMap(const char* filePath);

	Tmx::Map                        *mMap;
	std::map<int, Sprite*>          mListTileSet;
	Camera                          *mCamera;
	QuadTree                        *mQuadTree;
	std::vector<Brick*>             mListBricks;

public:
	explicit GameMap(const char* filePath);
    void SetCamera(Camera* camera);
    void Update(float dt);
    void Draw();
    Tmx::Map* GetMap();
    RECT GetWorldMapBound();
    int GetWidth();
    int GetHeight();
    int GetTileWidth();
    int GetTileHeight();
    std::map<int, Sprite*> getListTileSet();

    bool IsBoundLeft();		//Check this camera on the left side with the world map
    bool IsBoundRight();	//Check this camera on the right side with the world map
    bool IsBoundTop();		//Check this camera on the Top side with the world map
    bool IsBoundBottom();	//Check this camera on the bottom side with the world map
    ~GameMap();

    std::vector<Brick*> GetListBrick();

    QuadTree* GetQuadTree();

};

#endif

