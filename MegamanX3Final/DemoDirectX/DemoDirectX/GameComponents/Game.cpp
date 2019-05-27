#include "Game.h"
#include "GameGlobal.h"
#include "../GameControllers/SceneManager.h"
#include "../Scenes/BeginScene.h"
#include "GameTime.h"

Game::Game(int fps)
{
	_FPS = fps;
	SceneManager::GetInstance()->ReplaceScene(new BeginScene());
	InitLoop();
}

void Game::Update(float dt)
{
	SceneManager::GetInstance()->GetCurrentScene()->update(dt);
	Render();
}

void Game::Render()
{
	auto device = GameGlobal::GetDevice();
	auto scene = SceneManager::GetInstance()->GetCurrentScene();
	device->Clear(0, NULL, D3DCLEAR_TARGET, scene->getBackColor(), 0.0f, 0);

	{
		device->BeginScene();

		//Starting draw
		GameGlobal::GetSpriteHandler()->Begin(D3DXSPRITE_ALPHABLEND);

		//draw here
		scene->draw();

		//Ending draw
		GameGlobal::GetSpriteHandler()->End();

		device->EndScene();
	}

	device->Present(NULL, NULL, NULL, NULL);
}

void Game::InitLoop() const
{
	MSG Msg;
	ZeroMemory(&Msg, sizeof(MSG));

	LARGE_INTEGER Frequency;
	QueryPerformanceFrequency(&Frequency);

	LARGE_INTEGER startTime;
	QueryPerformanceCounter(&startTime);

	LARGE_INTEGER endTime;
	LARGE_INTEGER currentTime;

	float frame_rate = 1.0f / _FPS;
	float gameTime = 0;

	while (Msg.message != WM_QUIT)
	{
		if (PeekMessage(&Msg, NULL, NULL, NULL, PM_REMOVE))
		{
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		}
		else
		{
			QueryPerformanceCounter(&endTime);
			gameTime = (endTime.QuadPart - startTime.QuadPart) * (1.0f / Frequency.QuadPart);
			if (gameTime >= frame_rate)
			{
				startTime = endTime;
				Update(gameTime);
			}
			else
			{
				Sleep(DWORD((frame_rate - gameTime) * 100));
			}
		}
	}
}
