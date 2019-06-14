#include "IntroScene.h"

IntroScene::IntroScene()
{
	_backColor = 0x000000;
	_animation_background = new Animation("Resources/IntroBackground/2342tilescreen.png", 1, 1, 256, 224);
}

IntroScene::~IntroScene()
{
	delete _animation_background;
}

void IntroScene::draw()
{
	_animation_background->draw();
}

void IntroScene::onKeyDown(int keyCode)
{
	_keys[keyCode] = true;
}

void IntroScene::onKeyUp(int keyCode)
{
	_keys[keyCode] = false;
}

void IntroScene::OnMouseDown(float x, float y)
{
}

void IntroScene::update(float dt)
{
	_animation_background->update(dt);
}
