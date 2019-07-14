#include "GameGlobal.h"

HINSTANCE GameGlobal::_hInstance = nullptr;
HWND GameGlobal::_hWnd = nullptr;
LPD3DXSPRITE GameGlobal::_spriteHandler = nullptr;
int GameGlobal::_width = 256;
int GameGlobal::_height = 256;
LPDIRECT3DDEVICE9 GameGlobal::_d3ddv = nullptr;
bool GameGlobal::_IsGameRunning = true;
IDirect3DSurface9* GameGlobal::_BackSurface = nullptr;
Keyboard* GameGlobal::_keyboard = nullptr;


void GameGlobal::setDevice(LPDIRECT3DDEVICE9 device)
{
	_d3ddv = device;
}

LPDIRECT3DDEVICE9 GameGlobal::getDevice()
{
	return _d3ddv;
}

HINSTANCE GameGlobal::getHinstance()
{
	return _hInstance;
}

HWND GameGlobal::getWnd()
{
	return _hWnd;
}

void GameGlobal::setHinstance(HINSTANCE hInstance)
{
	GameGlobal::_hInstance = hInstance;
}

void GameGlobal::setWnd(HWND hWnd)
{
	GameGlobal::_hWnd = hWnd;
}

void GameGlobal::setDXSprite(LPD3DXSPRITE spriteHandler)
{
	GameGlobal::_spriteHandler = spriteHandler;
}

LPD3DXSPRITE GameGlobal::getDXSprite()
{
	return _spriteHandler;
}

void GameGlobal::setWidth(int width)
{
	GameGlobal::_width = width;
}

int GameGlobal::getWidth()
{
	return _width;
}

void GameGlobal::setHeight(int height)
{
	GameGlobal::_height = height;
}

int GameGlobal::getHeight()
{
	return _height;
}

void GameGlobal::setIsGameRunning(bool val)
{
	_IsGameRunning = val;
}

bool GameGlobal::getIsGameRunning()
{
	return _IsGameRunning;
}

LPDIRECT3DSURFACE9 GameGlobal::getBackSurface()
{
	return _BackSurface;
}

void GameGlobal::setBackSurface(LPDIRECT3DSURFACE9 val)
{
	_BackSurface = val;
}

void GameGlobal::setKeyboard(Keyboard* keyboard)
{
	_keyboard = keyboard;
}

Keyboard* GameGlobal::getKeyboard()
{
	return _keyboard;
}
