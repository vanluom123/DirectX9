#include "Game.h"
#include "GameGlobal.h"
#include "Sprite.h"
#include "GameTime.h"
#include "SceneManager.h"
#include "DemoScene.h"

//Sprite *sprite;

Game::Game(int fps)
{
	mFPS = float(fps);

	/*sprite = new Sprite("Resources/naruto.png");
	sprite->SetPosition(float(GameGlobal::GetWidth() / 2), float(GameGlobal::GetHeight() / 2));*/

	SceneManager::GetInstance()->ReplaceScene(new DemoScene());

	InitLoop();
}

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

	device->Present(0, 0, 0, 0);
}

void Game::InitLoop() const
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
