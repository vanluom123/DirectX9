#ifndef __DEMO_SCENE_H__
#define __DEMO_SCENE_H__

#include "../GameComponents/Scene.h"
#include "../GameComponents/Animation.h"
#include "../GameComponents/GameMap.h"
#include "../GameComponents/Camera.h"
#include "../GameObjects/Player/GamePlayer.h"
#include "../GameObjects/Enemies/Banger/Banger.h"
#include "../GameObjects/Enemies/Gunner/Gunner.h"
#include "../GameObjects/Enemies/Helit/Helit.h"

class BeginScene : public Scene
{

public:
	BeginScene();
	~BeginScene();

	void update(float dt) override;
	void draw() override;

	void onKeyDown(int keyCode) override;
	void onKeyUp(int keyCode) override;

protected:
	Animation *AniBackGround;
	void checkCollision(float dt);
	void checkCameraAndWorldMap(float dt);
	void checkCameraAndEnemies();

	static void checkCollision(Entity* obj, Entity* other, float dt);
	void checkCollision(Entity* obj, float dt);

	GameMap* pMap;
	GamePlayer* gp;
	Camera* pCamera;

	RECT CurentRoom;
	RECT nextRoom;
	std::vector<Entity*> ListEntityOut;
	std::vector<Entity*> List000;
	std::map<int, bool> keys;
	int direction = 0;
	bool isboss;
};
#endif