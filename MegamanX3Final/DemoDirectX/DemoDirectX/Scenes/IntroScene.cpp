#include "IntroScene.h"

IntroScene::IntroScene()
{
	mBackColor = 0x000000;
	backGround = new Animation("Resources/IntroBackground/2342tilescreen.png", 1, 1, 256, 224);
}

IntroScene::~IntroScene()
{
	delete backGround;
}

void IntroScene::draw()
{
	backGround->Draw();
}

void IntroScene::onKeyDown(int keyCode)
{
	if (keyCode == 0xd)
	{
	}
}

void IntroScene::onKeyUp(int keyCode)
{
}

void IntroScene::onMouseDown(float x, float y)
{
}

void IntroScene::update(float dt)
{
	backGround->Update(dt);
}
