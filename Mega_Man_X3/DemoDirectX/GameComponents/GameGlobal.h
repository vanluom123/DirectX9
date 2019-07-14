#ifndef __GAME_GLOBAL_H__
#define __GAME_GLOBAL_H__
#include <d3dx9.h>
#include <d3d9.h>
#include <Windows.h>
#include "Keyboard.h"

class GameGlobal
{
public:
	static HINSTANCE getHinstance();
	static void setHinstance(HINSTANCE hInstance);

	static HWND getWnd();
	static void setWnd(HWND hWnd);

	static void setDXSprite(LPD3DXSPRITE spriteHandler);
	static LPD3DXSPRITE getDXSprite();

	static void setDevice(LPDIRECT3DDEVICE9 device);
	static LPDIRECT3DDEVICE9 getDevice();

	static void setWidth(int width);
	static int getWidth();

	static void setHeight(int height);
	static int getHeight();

	static void setIsGameRunning(bool val);
	static bool getIsGameRunning();

	static LPDIRECT3DSURFACE9 getBackSurface();
	static void setBackSurface(LPDIRECT3DSURFACE9 val);

	static void setKeyboard(Keyboard* keyboard);
	static Keyboard* getKeyboard();

private:
	static HINSTANCE _hInstance; //current Windows HINSTANCE
	static HWND _hWnd; //current HWND
	static LPD3DXSPRITE _spriteHandler; //Current SpriteHandler
	static int _width, _height; //Size of windows
	static LPDIRECT3DDEVICE9 _d3ddv; //Current direct device
	static Keyboard* _keyboard;
	static LPDIRECT3DSURFACE9 _BackSurface;
	static bool _IsGameRunning; //Game State
};

#endif
