#include "IntroScene.h"

IntroScene::IntroScene()
{
	_backColor = 0x000000;
	backGround = new Animation("Resources/IntroBackground/2342tilescreen.png", 1, 1, 256, 224);
}

IntroScene::~IntroScene()
{
	delete backGround;
}

void IntroScene::Draw()
{
	backGround->Draw();
}

void IntroScene::OnKeyDown(int keyCode)
{
	if (keyCode == 0xd)
	{
	}
}

void IntroScene::OnKeyUp(int keyCode)
{
}

void IntroScene::OnMouseDown(float x, float y)
{
}

void IntroScene::Update(float dt)
{
	backGround->Update(dt);
}
