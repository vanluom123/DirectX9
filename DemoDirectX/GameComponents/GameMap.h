#ifndef _GAME_MAP_H
#define _GAME_MAP_H

#include <vector>
#include "../GameComponents/Sprite.h"
#include "Camera.h"
#include "QuadTree.h"
#include "../GameObjects/Player/Player.h"
#include <iostream>
#include <MapReader/Tmx.h.in>

class GameMap
{
private:
	Sprite * _tileMap;
	Sprite * _tileMap1;
	Tmx::Map * _pTmxMap;

	std::vector<BaseObject *> _listEnemies;
	std::vector<RECT> _listRoom;

	RECT _srect;

	GameMap() { }
	static GameMap * s_instance;

public:
	~GameMap();
	static GameMap * getInstance();
	static void release();

	void initialize(const char * filePath);

	void loadMap();
	void update(float dt);
	void draw();
	void draw1();

public:
	int getWidth() const;
	int getHeight() const;

	int getTileWidth() const;
	int getTileHeight() const;

	std::vector<RECT> getListRoom() const;

};
#endif // _GAME_MAP_H
