#include "Game.h"
#include "GameGlobal.h"
#include "../GameControllers/SceneManager.h"
#include "../Scenes/BeginScene.h"

Game::Game(int fps)
{
	_FPS = fps;
	SceneManager::getInstance()->replaceScene(new BeginScene());
	this->initLoop();
}

void Game::update(float dt)
{
	SceneManager::getInstance()->getCurrentScene()->update(dt);
	this->render();
}

void Game::render()
{
	auto device = GameGlobal::getInstance()->getDevice();
	auto scene = SceneManager::getInstance()->getCurrentScene();
	device->Clear(0, NULL, D3DCLEAR_TARGET, scene->getBackColor(), 0.0f, 0);

	if (SUCCEEDED(device->BeginScene()))
	{
		//Starting draw
		GameGlobal::getInstance()->getDXSprite()->Begin(D3DXSPRITE_ALPHABLEND);

		//draw here
		scene->draw();

		//Ending draw
		GameGlobal::getInstance()->getDXSprite()->End();

		device->EndScene();
	}

	device->Present(NULL, NULL, NULL, NULL);
}

void Game::initLoop()
{
	MSG Msg;
	ZeroMemory(&Msg, sizeof(MSG));

	LARGE_INTEGER Frequency;
	QueryPerformanceFrequency(&Frequency);

	LARGE_INTEGER startTime;
	QueryPerformanceCounter(&startTime);

	LARGE_INTEGER endTime;

	float fFrameRate = 1.0f / _FPS;
	float fGameTime = 0;

	/*while (Msg.message != WM_QUIT)
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
				update(gameTime);
			}
			else
				Sleep(DWORD((frame_rate - gameTime) * 100));
		}
	}*/


	while (GameGlobal::getInstance()->IsGameRunning())
	{
		if (PeekMessage(&Msg, NULL, NULL, NULL, PM_REMOVE))
		{
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		}
		else
		{
			QueryPerformanceCounter(&endTime);
			fGameTime = (endTime.QuadPart - startTime.QuadPart) * (1.0f / Frequency.QuadPart);
			if (fGameTime >= fFrameRate)
			{
				startTime = endTime;
				this->update(fGameTime);
			}
			else
				Sleep(DWORD((fFrameRate - fGameTime) * 100));
		}
	}
}
