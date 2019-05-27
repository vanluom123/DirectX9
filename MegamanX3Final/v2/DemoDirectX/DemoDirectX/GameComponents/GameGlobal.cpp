#include "GameGlobal.h"

HINSTANCE GameGlobal::_hInstance = nullptr;
HWND GameGlobal::_hWnd = nullptr;
LPD3DXSPRITE GameGlobal::_spriteHandler = nullptr;
int GameGlobal::_width = 256;
int GameGlobal::_height = 256;
LPDIRECT3DDEVICE9 GameGlobal::_d3ddv = nullptr;
bool GameGlobal::isGameRunning = true;
IDirect3DSurface9* GameGlobal::backSurface = nullptr;


void GameGlobal::SetDevice(LPDIRECT3DDEVICE9 device)
{
	_d3ddv = device;
}

LPDIRECT3DDEVICE9 GameGlobal::GetDevice()
{
	return _d3ddv;
}

HINSTANCE GameGlobal::GetHINSTANCE()
{
	return _hInstance;
}

HWND GameGlobal::GetHWND()
{
	return _hWnd;
}

void GameGlobal::SetHINSTANCE(HINSTANCE hInstance)
{
	GameGlobal::_hInstance = hInstance;
}

void GameGlobal::SetHWND(HWND hWnd)
{
	GameGlobal::_hWnd = hWnd;
}

void GameGlobal::SetSpriteHandler(LPD3DXSPRITE spriteHandler)
{
	GameGlobal::_spriteHandler = spriteHandler;
}

LPD3DXSPRITE GameGlobal::GetSpriteHandler()
{
	return _spriteHandler;
}

void GameGlobal::SetWidth(int width)
{
	GameGlobal::_width = width;
}

int GameGlobal::GetWidth()
{
	return _width;
}

void GameGlobal::SetHeight(int height)
{
	GameGlobal::_height = height;
}

int GameGlobal::GetHeight()
{
	return _height;
}
