#include "DemoScene.h"
#include "GameGlobal.h"

DemoScene::DemoScene()
{
	DemoScene::LoadContent();
}

void DemoScene::Update(float dt)
{

	//this->mGoldBlock->Update(dt);
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
	this->mBackColor = 0x54acd2;

	this->mCamera = new Camera(GameGlobal::GetWidth(), GameGlobal::GetHeight());
	this->mMap = new GameMap("Resources/marioworld1-1.tmx");

	this->mCamera->SetPosition(float(GameGlobal::GetWidth()) / 2, float(this->mMap->GetHeight() - GameGlobal::GetHeight()) / 2);

	this->mMap->SetCamera(this->mCamera);


	//this->mGoldBlock = new Animation("Resources/Cat.png", 8, 2, 4);
	//this->mGoldBlock->SetPosition(float(GameGlobal::GetWidth()) / 2, float(GameGlobal::GetHeight()) / 2);
	//this->mGoldBlock->SetScale(D3DXVECTOR2(1, 1));

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
	this->mMap->Draw();
	//this->mGoldBlock->Draw();
}

void DemoScene::KeyDown(int keyCode)
{
	/*if (keyCode == VK_LEFT)
		mGoldBlock->SetPosition(mGoldBlock->GetPosition() + D3DXVECTOR3(-10, 0, 0));
	if (keyCode == VK_RIGHT)
		mGoldBlock->SetPosition(mGoldBlock->GetPosition() + D3DXVECTOR3(10, 0, 0));
	if (keyCode == VK_UP)
		mGoldBlock->SetPosition(mGoldBlock->GetPosition() + D3DXVECTOR3(0, -10, 0));
	if (keyCode == VK_DOWN)
		mGoldBlock->SetPosition(mGoldBlock->GetPosition() + D3DXVECTOR3(0, 10, 0));*/
}

void DemoScene::KeyUp(int keyCode)
{
}

void DemoScene::MouseDown(float x, float y)
{
}

DemoScene::~DemoScene()
{
	if (this->mMap)
	{
		delete this->mMap;
		this->mMap = nullptr;
	}
	if (this->mCamera)
	{
		delete this->mCamera;
		this->mCamera = nullptr;
	}
}
