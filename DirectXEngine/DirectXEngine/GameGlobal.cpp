#include "GameGlobal.h"

HINSTANCE GameGlobal::m_hInstance = NULL;
HWND GameGlobal::m_hWnd = NULL;
LPD3DXSPRITE GameGlobal::mSpriteHandler = NULL;
int GameGlobal::mWidth = 600;
int GameGlobal::mHeight = 600;
LPDIRECT3DDEVICE9 GameGlobal::mDevice = NULL;
bool GameGlobal::isGameRunning = true;
IDirect3DSurface9* GameGlobal::backSurface = NULL;

void GameGlobal::SetCurrentDevice(LPDIRECT3DDEVICE9 device)
{
	mDevice = device;
}

LPDIRECT3DDEVICE9 GameGlobal::GetCurrentDevice()
{
	return mDevice;
}


GameGlobal::GameGlobal()
{
}

GameGlobal::~GameGlobal()
{
}

HINSTANCE GameGlobal::GetCurrent_hInstance()
{
	return m_hInstance;
}

HWND GameGlobal::GetCurrent_hWnd()
{
	return m_hWnd;
}

void GameGlobal::SetCurrent_hInstance(HINSTANCE hInstance)
{
	m_hInstance = hInstance;
}

void GameGlobal::SetCurrent_hWnd(HWND hWnd)
{
	m_hWnd = hWnd;
}

void GameGlobal::SetCurrentSpriteHandler(LPD3DXSPRITE spriteHandler)
{
	mSpriteHandler = spriteHandler;
}

LPD3DXSPRITE GameGlobal::GetCurrentSpriteHandler()
{
	return mSpriteHandler;
}

void GameGlobal::SetWidth(int width)
{
	mWidth = width;
}

int GameGlobal::GetWidth()
{
	return mWidth;
}

void GameGlobal::SetHeight(int height)
{
	mHeight = height;
}

int GameGlobal::GetHeight()
{
	return mHeight;
}