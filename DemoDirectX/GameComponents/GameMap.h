#ifndef _GAME_MAP_H
#define _GAME_MAP_H

#include <vector>
#include "../GameComponents/Sprite.h"
#include "../GameObjects/Player/Player.h"
#include <tmxparser/Tmx.h>

class GameMap
{
	Sprite * m_pTileMap;
	Sprite * m_pTileMap1;
	Tmx::Map * m_pMap;

	std::vector<BaseObject *> m_lstEnemies;
	std::vector<RECT> m_lstRoom;

	RECT m_rc;

	GameMap();
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

	int getWidth() const;
	int getHeight() const;

	int getTileWidth() const;
	int getTileHeight() const;

	std::vector<RECT> getListRoom() const;

};
#endif // _GAME_MAP_H
