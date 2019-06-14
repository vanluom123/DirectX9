#ifndef _GAME_MAP_H
#define _GAME_MAP_H

#include <vector>
#include "../GameComponents/Sprite.h"
#include "Camera.h"
#include "QuadTree.h"
#include "../GameObjects/Player/Player.h"
#include <iostream>
#include "../MapReader/Tmx.h.in"

class GameMap
{
public:
	GameMap(const char* filePath);
	~GameMap();

	void loadMap();
	void update(float dt);
	void draw();
	void draw1();


	// SUB-FUNCTION
public:
	int getWidth() const;
	int getHeight() const;

	int getTileWidth() const;
	int getTileHeight() const;

	bool isBoundLeft() const; //Check this camera on the left side with the world map
	bool isBoundRight() const; //Check this camera on the right side with the world map
	bool isBoundTop() const; //Check this camera on the Top side with the world map
	bool isBoundBottom() const; //Check this camera on the bottom side with the world map

	void setViewport(Camera* camera);
	void setPlayer(Player* player);

	std::vector<BaseObject*> getListEnemies() const;
	std::vector<RECT> getListRoom() const;
	QuadTree* getQuadTree() const;
	Tmx::Map* getMap() const;
	RECT getWorldMapBound() const;

private:
	Sprite* _tileMap;
	Sprite* _tileMap1;
	Tmx::Map* _pTmxMap;
	Camera* _viewport;
	QuadTree* _quadTree;
	std::vector<BaseObject*> _listEnemies;
	std::vector<RECT> _listRoom;
	RECT _srect;
	Player* _player;

};
#endif // _GAME_MAP_H
