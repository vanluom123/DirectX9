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
	Animation *_pAniBackground;
	void CheckCollision(float dt);
	void CheckCameraAndWorldMap(float dt);
	void CheckCameraAndEnemies();

	static void CheckCollision(BaseObject* obj, BaseObject* other, float dt);
	void CheckCollision(BaseObject* obj, float dt);

	GameMap* _pMap;
	Player* _pPlayer;
	Camera* _pCamera;

	RECT _curentRoom;
	RECT _nextRoom;
	std::vector<BaseObject*> _listEntityOut;
	std::vector<BaseObject*> _list000;
	std::map<int, bool> _keys;
	int _direction = 0;
	bool _isboss;
};
#endif