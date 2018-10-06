#include "DemoScene.h"
#include "GameGlobal.h"

DemoScene::DemoScene()
{
	mGoldBlock = nullptr;
	DemoScene::LoadContent();
}

void DemoScene::Update(float dt)
{
	mGoldBlock->Update(dt);
	////cong don thoi gian lai 60 FPS = 1 / 60 giay trong 1 lan goi update
	//mTimeCounter += dt;

	////update sau 1 giay
	//if (mTimeCounter >= 1.0f)
	//{
	//	for (Sprite *child : mSprite)
	//	{
	//		//set lai position random tu 0 -> 500 theo x va y cho moi sprite
	//		child->SetPosition(float(rand() % 500), float(rand() % 500));
	//	}

	//	//Set lai thoi gian
	//	mTimeCounter = 0;
	//}
}

void DemoScene::LoadContent()
{
	mBackColor = 0x54acd2;
	//mGoldBlock = new Animation("Resources/goldbrick.png", 4, 1, 4, 0.15);
	mGoldBlock = new Animation("Resources/Cat.png", 8, 2, 4);
	mGoldBlock->SetPosition(float(GameGlobal::GetWidth()) / 2, float(GameGlobal::GetHeight()) / 2);
	mGoldBlock->SetScale(D3DXVECTOR2(1, 1));
	////Set time counter = 0
	//mTimeCounter = 0;

	////Set back color cho scene o day la mau xanh
	//mBackColor = 0x54acd2;

	//for (int i = 0; i < 10; ++i)
	//{
	//	//Tao normalbrick tu hinh anh theo huong dan
	//	Sprite* sprite = new Sprite("Resources/naruto.png");

	//	//Set random position cho cac sprite tu 0 -> 500 theo x va y
	//	sprite->SetPosition(float(rand() % 500), float(rand() % 500));

	//	//Them sprite vao vector
	//	mSprite.push_back(sprite);
	//}
}

void DemoScene::Draw()
{
	////goi va draw cac sprite trong vector
	//for (Sprite* child : mSprite)
	//	child->Draw();
	mGoldBlock->Draw();
}