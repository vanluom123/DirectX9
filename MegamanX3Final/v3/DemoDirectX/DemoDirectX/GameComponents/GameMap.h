#pragma once
#include <vector>
#include "../GameComponents/Sprite.h"
#include <Tmx.h.in>
#include "Camera.h"
#include "QuadTree.h"
#include "../GameObjects/Player/Player.h"
using namespace std;

class GameMap
{
public:
	GameMap(const char* filePath);
	~GameMap();

	void LoadMap();
	void Update(float dt);
	void Draw();
	void Draw1();


	// SUB-FUNCTION
public:
	int GetWidth() const;
	int GetHeight() const;

	int GetTileWidth() const;
	int GetTileHeight() const;

	bool IsBoundLeft() const; //Check this camera on the left side with the world map
	bool IsBoundRight() const; //Check this camera on the right side with the world map
	bool IsBoundTop() const; //Check this camera on the Top side with the world map
	bool IsBoundBottom() const; //Check this camera on the bottom side with the world map

	void SetCamera(Camera* camera);
	void SetPlayer(Player* player);

	std::vector<BaseObject*> GetListEnemies() const;

	std::vector<RECT> GetListRoom() const;

	QuadTree* GetQuadTree() const;

	Tmx::Map* GetMap() const;

	RECT GetWorldMapBound() const;

private:
	Sprite* m_tileMap;
	Sprite* m_tileMap1;

	Tmx::Map* m_tmxMap;

	Camera* m_camera;

	QuadTree* m_quadTree;

	std::vector<BaseObject*> m_listEnemies;

	std::vector<RECT> m_listRoom;

	RECT m_sourceRect;

	Player* m_player;

};
