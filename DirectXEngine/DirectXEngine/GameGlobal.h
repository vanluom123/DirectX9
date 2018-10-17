#ifndef __GAME_GLOBAL__
#define __GAME_GLOBAL__
#include <d3dx9.h>
#include <d3d9.h>
#include <Windows.h>

class GameGlobal
{
public:
	GameGlobal();
	~GameGlobal();

	static HINSTANCE GetCurrent_hInstance();
	static HWND GetCurrent_hWnd();

	static void SetCurrent_hInstance(HINSTANCE hInstance);
	static void SetCurrent_hWnd(HWND hWnd);

	static void SetCurrentSpriteHandler(LPD3DXSPRITE spriteHandler);
	static LPD3DXSPRITE GetCurrentSpriteHandler();

	static void SetCurrentDevice(LPDIRECT3DDEVICE9 device);
	static LPDIRECT3DDEVICE9 GetCurrentDevice();

	static void SetWidth(int width);
	static int GetWidth();

	static void SetHeight(int height);
	static int GetHeight();

	static LPDIRECT3DSURFACE9 backSurface;

	// Game status
	static bool isGameRunning;

private:
	// hInstance current
	static HINSTANCE m_hInstance;
	// hWnd current
	static HWND m_hWnd;
	// Sprite current
	static LPD3DXSPRITE mSpriteHandler;
	// Size Windows
	static int mWidth, mHeight;
	// Device DirectX current
	static LPDIRECT3DDEVICE9 mDevice;
};

#endif

