#include "FrameWork.h"
#include <windowsx.h>
#include "GameComponents\GameGlobal.h"
#include "GameControllers\SceneManager.h"

FrameWork::FrameWork()
{}

FrameWork::~FrameWork()
{
	if (FULL_SCREEN)
		ChangeDisplaySettings(NULL, 0);

	UnregisterClass(m_applicationName, m_hInstance);
	m_hInstance = NULL;
}

bool FrameWork::Initialize()
{
	return CreateDX3DWindows(
		"GAME_TUTORIAL",
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		GameGlobal::GetWidth(),
		GameGlobal::GetHeight()
	);
}

bool FrameWork::CreateDX3DWindows(const char* szTitleName, int x, int y, int width, int height)
{
	WNDCLASSEX wc;

	m_applicationName = szTitleName;

	m_hInstance = GetModuleHandle(NULL);

	//Setup the windows class with default settings
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WNDPROC(WndProc);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = HBRUSH(GetStockObject(BLACK_BRUSH));
	wc.lpszMenuName = NULL;
	wc.lpszClassName = m_applicationName;
	wc.cbSize = sizeof(WNDCLASSEX);

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "RegisterClassEx() failed", "Error", MB_OK);
		return false;
	}

	auto screenWidth = GetSystemMetrics(SM_CXSCREEN);
	auto screenHeight = GetSystemMetrics(SM_CYSCREEN);
	int style;

	if (FULL_SCREEN)
	{
		DEVMODE dmScreenSettings;
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = static_cast<unsigned long>(screenWidth);
		dmScreenSettings.dmPelsHeight = static_cast<unsigned long>(screenHeight);
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Change the display settings to full screen.
		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);
		style = WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP;

	}
	else
	{
		screenWidth = width;
		screenHeight = height;
		style = WS_OVERLAPPEDWINDOW;
	}


	HWND hWnd = CreateWindow(
		m_applicationName,
		szTitleName,
		style,
		x,
		y,
		screenWidth,
		screenHeight,
		NULL,
		NULL,
		m_hInstance,
		NULL);

	GameGlobal::SetCurrentHWND(hWnd);
	GameGlobal::SetCurrentHINSTACE(m_hInstance);

	if (!hWnd)
	{
		MessageBox(NULL, "CreateWindowEx() failed", "Error", MB_OK);
		PostQuitMessage(0);
		return false;
	}


	ShowWindow(hWnd, SW_SHOW);
	SetForegroundWindow(hWnd);
	SetFocus(hWnd);

	if (InitializeDevice3D())
		auto m_game = new Game();

	return true;
}

bool FrameWork::InitializeDevice3D()
{
	m_d3d = Direct3DCreate9(D3D_SDK_VERSION);

	if (!m_d3d)
		return false;

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.Windowed = !(FULL_SCREEN);
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferHeight = GameGlobal::GetHeight();
	d3dpp.BackBufferWidth = GameGlobal::GetWidth();

	//Create DirectX 3D device
	HRESULT resultD3D = m_d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		GameGlobal::getCurrentHWND(),
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&m_d3ddv);

	if (FAILED(resultD3D))
	{
		MessageBox(NULL, "CreateDevice failed", "Error", MB_OK);
		return false;
	}

	GameGlobal::SetCurrentDevice(m_d3ddv);

	HRESULT result = D3DXCreateSprite(m_d3ddv, &m_spriteHandler);
	if (FAILED(result))
	{
		MessageBox(NULL, "D3DXCreateSprite failed", "Error", MB_OK);
		return false;
	}

	GameGlobal::SetCurrentSpriteHandler(m_spriteHandler);

	return true;
}

LRESULT FrameWork::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;

	switch (message)
	{
		case WM_LBUTTONDOWN:
		{
			SceneManager::GetInstance()->GetCurrentScene()->OnMouseDown(
				GET_X_LPARAM(wParam),
				GET_Y_LPARAM(wParam)
			);
		}
		case WM_KEYUP:
		{
			SceneManager::GetInstance()->GetCurrentScene()->OnKeyUp(wParam);
			break;
		}
		case WM_KEYDOWN:
		{
			SceneManager::GetInstance()->GetCurrentScene()->OnKeyDown(wParam);
			if (wParam == VK_ESCAPE)
			{
				UINT confirmExitGame = 0;
				MessageBox(hWnd, "Do you want to exit game?", "Confirm", confirmExitGame);
				if (confirmExitGame == MB_OK)
				{
					PostQuitMessage(0);
					DestroyWindow(hWnd);
				}
			}
			break;
		}
		case WM_PAINT:
		{
			HDC hdc = BeginPaint(hWnd, &ps);
			EndPaint(hWnd, &ps);
			break;
		}
		case WM_CLOSE:
		{
			GameGlobal::isGameRunning = false;
			PostQuitMessage(0);
			DestroyWindow(hWnd);
			break;
		}
		default: {
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	};

	return 0;
}