#include "DemoScene.h"
#include "GameGlobal.h"
#include "Player.h"

DemoScene::DemoScene(): mMap(nullptr), mCamera(nullptr), mPlayer(nullptr)
{
	DemoScene::LoadContent();
}

void DemoScene::Update(float dt)
{
	mPlayer->HandlerKeyboard(keys);
	mPlayer->Update(dt);
}

void DemoScene::LoadContent()
{
	mBackColor = 0x54acd2;

	mCamera = new Camera(GameGlobal::GetWidth(), GameGlobal::GetHeight());
	mMap = new GameMap("Resources/marioworld1-1.tmx");

	mCamera->SetPosition(float(GameGlobal::GetWidth()) / 2, mMap->GetHeight() - float(GameGlobal::GetHeight()) / 2);

	mMap->SetCamera(mCamera);

	mPlayer = new Player();
	mPlayer->SetPosition(float(GameGlobal::GetWidth()) / 2, float(GameGlobal::GetHeight()) / 2);
}

void DemoScene::Draw()
{
	mMap->Draw();
	mPlayer->Draw();
}

void DemoScene::KeyDown(int keyCode)
{
	keys[keyCode] = true;
	mPlayer->OnKeyPressed(keyCode);

	//switch(keyCode)
	//{
	//	case VK_LEFT:
	//		mCamera->SetPosition(mCamera->GetPosition() + D3DXVECTOR3(-10, 0, 0));
	//		break;
	//	case VK_RIGHT:
	//		mCamera->SetPosition(mCamera->GetPosition() + D3DXVECTOR3(10, 0, 0));
	//		break;
	//	case VK_UP:
	//		mCamera->SetPosition(mCamera->GetPosition() + D3DXVECTOR3(0, -10, 0));
	//		break;
	//	case VK_DOWN:
	//		mCamera->SetPosition(mCamera->GetPosition() + D3DXVECTOR3(0, 10, 0));
	//		break;
	//	default:break;
	//}
}

void DemoScene::KeyUp(int keyCode)
{
	keys[keyCode] = false;
}

void DemoScene::MouseDown(float x, float y)
{}

DemoScene::~DemoScene()
{
	if (mMap)
	{
		delete mMap;
		mMap = nullptr;
	}
	if (mCamera)
	{
		delete mCamera;
		mCamera = nullptr;
	}
}
