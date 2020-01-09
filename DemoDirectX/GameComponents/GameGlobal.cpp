#include "GameGlobal.h"

GameGlobal* GameGlobal::s_instance = nullptr;

void GameGlobal::setDevice(LPDIRECT3DDEVICE9 device)
{
	_d3ddv = device;
}

LPDIRECT3DDEVICE9 GameGlobal::getDevice()
{
	return _d3ddv;
}

GameGlobal::~GameGlobal()
{
}

GameGlobal* GameGlobal::getInstance()
{
	if (!s_instance)
		s_instance = new GameGlobal();
	return s_instance;
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
	_hInstance = hInstance;
}

void GameGlobal::setWnd(HWND hWnd)
{
	_hWnd = hWnd;
}

void GameGlobal::setDXSprite(LPD3DXSPRITE spriteHandler)
{
	_spriteHandler = spriteHandler;
}

LPD3DXSPRITE GameGlobal::getDXSprite()
{
	return _spriteHandler;
}

void GameGlobal::setWidth(int width)
{
	_width = width;
}

int GameGlobal::getWidth()
{
	return _width;
}

void GameGlobal::setHeight(int height)
{
	_height = height;
}

int GameGlobal::getHeight()
{
	return _height;
}

void GameGlobal::IsGameRunning(bool val)
{
	_IsGameRunning = val;
}

bool GameGlobal::IsGameRunning()
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

GameGlobal::GameGlobal()
{
	_hInstance = nullptr;
	_hWnd = nullptr;
	_spriteHandler = nullptr;
	_width = 256;
	_height = 256;
	_d3ddv = nullptr;
	_IsGameRunning = true;
	_BackSurface = nullptr;
}
