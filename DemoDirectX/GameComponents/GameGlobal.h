#ifndef __GAME_GLOBAL_H__
#define __GAME_GLOBAL_H__
#include <d3dx9.h>
#include <d3d9.h>
#include <Windows.h>

class GameGlobal
{
public:
	~GameGlobal();
	static GameGlobal* getInstance();

	HINSTANCE getHinstance();
	void setHinstance(HINSTANCE hInstance);

	HWND getWnd();
	void setWnd(HWND hWnd);

	void setDXSprite(LPD3DXSPRITE spriteHandler);
	LPD3DXSPRITE getDXSprite();

	void setDevice(LPDIRECT3DDEVICE9 device);
	LPDIRECT3DDEVICE9 getDevice();

	void setWidth(int width);
	int getWidth();

	void setHeight(int height);
	int getHeight();

	void IsGameRunning(bool val);
	bool IsGameRunning();

	LPDIRECT3DSURFACE9 getBackSurface();
	void setBackSurface(LPDIRECT3DSURFACE9 val);

private:
	GameGlobal();
	static GameGlobal* s_instance;

	HINSTANCE _hInstance; //current Windows HINSTANCE
	HWND _hWnd; //current HWND
	LPD3DXSPRITE _spriteHandler; //Current SpriteHandler
	int _width, _height; //Size of windows
	LPDIRECT3DDEVICE9 _d3ddv; //Current direct device
	LPDIRECT3DSURFACE9 _BackSurface;
	bool _IsGameRunning; //Game State
};

#endif
