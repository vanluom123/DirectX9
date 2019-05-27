#include "GameGlobal.h"

HINSTANCE GameGlobal::m_hInstance = nullptr;
HWND GameGlobal::m_hWnd = nullptr;
LPD3DXSPRITE GameGlobal::m_spriteHandler = nullptr;
int GameGlobal::m_width = 256;
int GameGlobal::m_height = 256;
LPDIRECT3DDEVICE9 GameGlobal::m_d3ddv = nullptr;
bool GameGlobal::isGameRunning = true;
IDirect3DSurface9* GameGlobal::backSurface = nullptr;


void GameGlobal::SetDevice(LPDIRECT3DDEVICE9 device)
{
	m_d3ddv = device;
}

LPDIRECT3DDEVICE9 GameGlobal::GetDevice()
{
	return m_d3ddv;
}

HINSTANCE GameGlobal::GetHINSTANCE()
{
	return m_hInstance;
}

HWND GameGlobal::GetHWND()
{
	return m_hWnd;
}

void GameGlobal::SetHINSTANCE(HINSTANCE hInstance)
{
	GameGlobal::m_hInstance = hInstance;
}

void GameGlobal::SetHWND(HWND hWnd)
{
	GameGlobal::m_hWnd = hWnd;
}

void GameGlobal::SetSpriteHandler(LPD3DXSPRITE spriteHandler)
{
	GameGlobal::m_spriteHandler = spriteHandler;
}

LPD3DXSPRITE GameGlobal::GetSpriteHandler()
{
	return m_spriteHandler;
}

void GameGlobal::SetWidth(int width)
{
	GameGlobal::m_width = width;
}

int GameGlobal::GetWidth()
{
	return m_width;
}

void GameGlobal::SetHeight(int height)
{
	GameGlobal::m_height = height;
}

int GameGlobal::GetHeight()
{
	return m_height;
}
