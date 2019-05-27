#ifndef __DEMO_SCENE_H__
#define __DEMO_SCENE_H__

#include "../GameComponents/Scene.h"
#include "../GameComponents/Animation.h"
#include "../GameComponents/GameMap.h"
#include "../GameComponents/Camera.h"
#include "../GameObjects/Player/Player.h"
#include "../GameObjects/Enemies/Banger/Banger.h"
#include "../GameObjects/Enemies/Gunner/Gunner.h"
#include "../GameObjects/Enemies/Helit/Helit.h"

class BeginScene : public Scene
{

public:
	BeginScene();
	~BeginScene();

	void Update(float dt) override;
	void Draw() override;

	void OnKeyDown(int keyCode) override;
	void OnKeyUp(int keyCode) override;

protected:
	Animation *m_animBackground;
	void CheckCollision(float dt);
	void CheckCameraAndWorldMap(float dt);
	void CheckCameraAndEnemies();

	static void CheckCollision(BaseObject* obj, BaseObject* other, float dt);
	void CheckCollision(BaseObject* obj, float dt);

	GameMap* m_gameMap;
	Player* m_player;
	Camera* m_camera;

	RECT m_currentRoom;
	RECT m_nextRoom;
	std::vector<BaseObject*> m_listEntityOut;
	std::vector<BaseObject*> m_list000;
	std::map<int, bool> m_key;
	int m_direction = 0;
	bool m_isBoss;
};
#endif