#pragma once
#include <d3dx9.h>
#include <d3d9.h>
#include <vector>

#include "../GameComponents/Sprite.h"
#include "../MapReader/Tmx.h.in"
#include "Camera.h"
#include "QuadTree.h"
#include "../GameObjects/Player/GamePlayer.h"

class GameMap
{
public:
	explicit GameMap(const char* filePath);

	void setCamera(Camera* camera);

	void update(float dt);
	void draw();
	void draw1();

	Tmx::Map* getMap() const;
	RECT getWorldMapBound() const;

	int getWidth() const;
	int getHeight() const;

	int getTileWidth() const;
	int getTileHeight() const;

	bool IsBoundLeft() const; //Check this camera on the left side with the world map
	bool IsBoundRight() const; //Check this camera on the right side with the world map
	bool IsBoundTop() const; //Check this camera on the Top side with the world map
	bool IsBoundBottom() const; //Check this camera on the bottom side with the world map
	void LoadMap();
	~GameMap();

	std::vector<Entity*> getListListEnemies() const;
	std::vector<RECT> getListRoom() const;

	GamePlayer*		gp;
	QuadTree* getQuadTree() const;
private:
	Sprite* TileMap;
	Sprite* TileMap1;
	Tmx::Map* pTmxMap;
	Camera* pCamera;
	QuadTree* pQuadTree;
	std::vector<Entity*> ListEnemies;
	std::vector<RECT> ListRoom;
	RECT sourceRECT;
};
