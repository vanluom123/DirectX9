#ifndef __GAME_GLOBAL_H__
#define __GAME_GLOBAL_H__
#include <d3dx9.h>
#include <d3d9.h>
#include <Windows.h>

class GameGlobal
{
public:
	static HINSTANCE GetHINSTANCE();
	static void SetHINSTANCE(HINSTANCE hInstance);

	static HWND GetHWND();
	static void SetHWND(HWND hWnd);

	static void SetSpriteHandler(LPD3DXSPRITE spriteHandler);
	static LPD3DXSPRITE GetSpriteHandler();

	static void SetDevice(LPDIRECT3DDEVICE9 device);
	static LPDIRECT3DDEVICE9 GetDevice();

	static void SetWidth(int width);
	static int GetWidth();

	static void SetHeight(int height);
	static int GetHeight();

	static LPDIRECT3DSURFACE9 backSurface;

	static bool isGameRunning; //Game State 

private:
	static HINSTANCE m_hInstance; //current Windows HINSTANCE
	static HWND m_hWnd; //current HWND
	static LPD3DXSPRITE m_spriteHandler; //Current SpriteHandler
	static int m_width, m_height; //Size of windows
	static LPDIRECT3DDEVICE9 m_d3ddv; //Current direct device
};

#endif
