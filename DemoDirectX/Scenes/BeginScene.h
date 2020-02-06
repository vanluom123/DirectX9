#ifndef __DEMO_SCENE_H__
#define __DEMO_SCENE_H__

#include "../GameComponents/Animation.h"
#include "../GameComponents/GameMap.h"
#include "../GameComponents/Camera.h"
#include "../GameObjects/Player/Player.h"
#include "../GameObjects/Enemies/Banger/Banger.h"
#include "Scene.h"

class BeginScene : public Scene
{
private:
	void checkCollision(float dt);
	void checkCollision(BaseObject * obj, BaseObject * other, float dt);
	void checkCollision(BaseObject * obj, float dt);

	Animation * _pAniBackground;

	RECT _curentRoom;
	RECT _nextRoom;

	vector<BaseObject *> _listEntityOut;
	vector<BaseObject *> _list000;

	map<int, bool> _keys;

	int _direction = 0;

	bool _isBoss;

public:
	BeginScene();
	~BeginScene();

	void update(float dt) override;
	void draw() override;

	void onKeyDown(int keyCode) override;
	void onKeyUp(int keyCode) override;

};
#endif