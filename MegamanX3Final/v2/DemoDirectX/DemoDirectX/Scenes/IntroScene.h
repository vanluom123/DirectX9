#ifndef __INTRO_SCENE_H__
#define __INTRO_SCENE_H__
#include "../GameComponents/Scene.h"
#include "../GameComponents/Animation.h"

class IntroScene : public Scene
{
public:
	IntroScene();
	~IntroScene();

	void Draw() override;

	void OnKeyDown(int keyCode) override;

	void OnKeyUp(int keyCode) override;

	void OnMouseDown(float x, float y);

	void Update(float dt) override;

private:
	Animation* backGround;
};

#endif