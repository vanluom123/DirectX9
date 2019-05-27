#include "IntroScene.h"

IntroScene::IntroScene()
{
	m_backColor = 0x000000;
	m_background = new Animation("Resources/IntroBackground/2342tilescreen.png", 1, 1, 256, 224);
}

IntroScene::~IntroScene()
{
	delete m_background;
}

void IntroScene::Draw()
{
	m_background->Draw();
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
	m_background->Update(dt);
}
