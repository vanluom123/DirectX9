#include "GameGlobal.h"

GameGlobal* GameGlobal::s_instance = nullptr;

void GameGlobal::setDevice(LPDIRECT3DDEVICE9 device)
{
	m_lpD3ddv = device;
}

LPDIRECT3DDEVICE9 GameGlobal::getDevice()
{
	return m_lpD3ddv;
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
	return m_hInstance;
}

HWND GameGlobal::getWnd()
{
	return m_hWnd;
}

void GameGlobal::setHinstance(HINSTANCE hInstance)
{
	m_hInstance = hInstance;
}

void GameGlobal::setWnd(HWND hWnd)
{
	m_hWnd = hWnd;
}

void GameGlobal::setDXSprite(LPD3DXSPRITE spriteHandler)
{
	m_lpSpriteHandler = spriteHandler;
}

LPD3DXSPRITE GameGlobal::getDXSprite()
{
	return m_lpSpriteHandler;
}

void GameGlobal::setWidth(int width)
{
	m_width = width;
}

int GameGlobal::getWidth()
{
	return m_width;
}

void GameGlobal::setHeight(int height)
{
	m_height = height;
}

int GameGlobal::getHeight()
{
	return m_height;
}

void GameGlobal::IsGameRunning(bool val)
{
	m_bGameRunning = val;
}

bool GameGlobal::IsGameRunning()
{
	return m_bGameRunning;
}

LPDIRECT3DSURFACE9 GameGlobal::getBackSurface()
{
	return m_lpBackSurface;
}

void GameGlobal::setBackSurface(LPDIRECT3DSURFACE9 val)
{
	m_lpBackSurface = val;
}

GameGlobal::GameGlobal()
{
	m_hInstance = nullptr;
	m_hWnd = nullptr;
	m_lpSpriteHandler = nullptr;
	m_width = 256;
	m_height = 256;
	m_lpD3ddv = nullptr;
	m_bGameRunning = true;
	m_lpBackSurface = nullptr;
}
