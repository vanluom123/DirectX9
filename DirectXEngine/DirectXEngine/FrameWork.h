#ifndef _FRAME_WORK_H
#define _FRAME_WORK_H

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "GameComponents\Game.h"

#define FULL_SCREEN false

class FrameWork
{
private:
	bool						CreateDX3DWindows(const char* szTitleName, int x, int y, int width, int height);
	bool						InitializeDevice3D();
	const char*					m_applicationName;
	HINSTANCE					m_hInstance;
	PDIRECT3D9					m_d3d;
	LPDIRECT3DDEVICE9			m_d3ddev;
	LPD3DXSPRITE				m_spriteHandler;

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

public:
	FrameWork();
	~FrameWork();

	bool Initialize();
};

#endif