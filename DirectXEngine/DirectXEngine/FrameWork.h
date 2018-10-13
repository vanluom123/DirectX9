#ifndef _FRAME_WORK_H
#define _FRAME_WORK_H

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "Game.h"

#define FULL_SCREEN false

class FrameWork
{
public:
	FrameWork();
	~FrameWork();

	bool Initialize();
	void Run();

private:
	bool						create_dx_window(const char* szTitleName, int x, int y, int width, int height);
	bool						init_device();
	const char*					m_applicationName;
	HINSTANCE					m_hInstance;
	PDIRECT3D9					d3d;
	LPDIRECT3DDEVICE9			d3ddev;
	LPD3DXSPRITE				m_SpriteHandler;

	Game *mGame;
};

#endif