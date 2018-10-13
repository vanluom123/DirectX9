#include "Game.h"
#include "GameGlobal.h"
#include "Sprite.h"
#include "GameTime.h"
#include "SceneManager.h"
#include "DemoScene.h"

Game::Game(int fps): mBackground(NULL), mBackBuffer(NULL), mWidth(0), mHeight(0)
{
	mFPS = float(fps);
	SceneManager::GetInstance()->ReplaceScene(new DemoScene());
}

Game::~Game()
{}

void Game::Update(float dt)
{
	SceneManager::GetInstance()->GetCurrentScene()->Update(dt);
	Render();
}

void Game::Render()
{
	auto device = GameGlobal::GetCurrentDevice();
	auto scene = SceneManager::GetInstance()->GetCurrentScene();

	//0x4866ff set mau cho surface
	device->Clear(0, NULL, D3DCLEAR_TARGET, scene->GetBackColor(), 0.0f, 0);

	{
		device->BeginScene();

		//bat dau ve
		GameGlobal::GetCurrentSpriteHandler()->Begin(D3DXSPRITE_ALPHABLEND);

		//draw here
		//sprite->Draw();
		scene->Draw();

		//ket thuc ve
		GameGlobal::GetCurrentSpriteHandler()->End();

		device->EndScene();
	}

	device->Present(NULL, NULL, NULL, NULL);
}

void Game::InitLoop()
{
	MSG msg;

	const float tick_per_frame = 1.0f / mFPS;
	float delta = 0;

	while (GameGlobal::isGameRunning)
	{
		GameTime::GetInstance()->StartCounter();

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		delta += GameTime::GetInstance()->GetCounter();

		if (delta >= tick_per_frame)
		{
			Update((delta));
			delta = 0;
		}
		else
		{
			Sleep(DWORD(tick_per_frame - delta));
			delta = tick_per_frame;
		}
	}
}
