#ifndef __INTRO_SCENE_H__
#define __INTRO_SCENE_H__
#include "../GameComponents/Scene.h"
#include "../GameComponents/Animation.h"

class IntroScene : public Scene
{
public:
	IntroScene();
	~IntroScene();

	void draw() override;

	void onKeyDown(int keyCode) override;

	void onKeyUp(int keyCode) override;

	void onMouseDown(float x, float y) override;

	void update(float dt) override;

private:
	Animation* backGround;
};

#endif