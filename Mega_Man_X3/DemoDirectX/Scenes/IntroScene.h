#ifndef __INTRO_SCENE_H__
#define __INTRO_SCENE_H__
#include "../GameComponents/Animation.h"
#include <map>
#include <memory>

#include "Scene.h"

class IntroScene : public Scene
{
public:
	IntroScene();
	~IntroScene();

	void onKeyDown(int keyCode) override;
	void onKeyUp(int keyCode) override;
	void OnMouseDown(float x, float y);
	void update(float dt) override;
	void draw() override;

private:
	Animation* _animation_background;
	std::map<bool, int> _keys;

};

#endif