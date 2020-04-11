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

	HINSTANCE m_hInstance;          //current Windows HINSTANCE
	HWND m_hWnd;                    //current HWND
	LPD3DXSPRITE m_lpSpriteHandler; //Current SpriteHandler
	int m_width;                    //Size of windows
	int m_height;
	LPDIRECT3DDEVICE9 m_lpD3ddv;    //Current direct device
	LPDIRECT3DSURFACE9 m_lpBackSurface;
	bool m_bGameRunning;            //Game State
};

#endif
