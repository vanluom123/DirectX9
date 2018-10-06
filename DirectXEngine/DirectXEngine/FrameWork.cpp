#include "FrameWork.h"
#include "Game.h"
#include "GameGlobal.h"

LRESULT CALLBACK wnd_proc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

FrameWork::~FrameWork()
{
	if (FULL_SCREEN)
		ChangeDisplaySettings(nullptr, 0);

	UnregisterClass(m_applicationName, m_hInstance);
	m_hInstance = nullptr;
}

bool FrameWork::Initialize()
{
	return create_dx_window(
		"Win32",
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		GameGlobal::GetWidth(),
		GameGlobal::GetHeight()
	);
}

void FrameWork::Run()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	//update loop
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			//Game loop
		}
	}
}

bool FrameWork::create_dx_window(const char* szTitleName, int x, int y, int width, int height)
{
	WNDCLASSEX wc;

	m_applicationName = szTitleName;

	m_hInstance = GetModuleHandle(nullptr);

	//Setup the windows class with default settings
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = wnd_proc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_hInstance;
	wc.hIcon = LoadIcon(nullptr, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = HBRUSH(GetStockObject(BLACK_BRUSH));
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = m_applicationName;
	wc.cbSize = sizeof(WNDCLASSEX);

	if (!RegisterClassEx(&wc))
	{
		MessageBox(nullptr, "RegisterClassEx() failed", "Error", MB_OK);
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


	HWND hwnd = CreateWindow(
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

	GameGlobal::SetCurrentHWND(hwnd);
	GameGlobal::SetCurrentHINSTACE(m_hInstance);

	if (!hwnd)
	{
		MessageBox(nullptr, "CreateWindowEx() failed", "Error", MB_OK);
		PostQuitMessage(0);
		return false;
	}


	ShowWindow(hwnd, SW_SHOW);
	SetForegroundWindow(hwnd);
	SetFocus(hwnd);

	if (init_device())
		Game* game = new Game();

	return true;
}

bool FrameWork::init_device()
{
	d3d = Direct3DCreate9(D3D_SDK_VERSION);

	if (!d3d)
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
	const auto resultD3D = d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		GameGlobal::getCurrentHWND(),
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3ddev);

	if (FAILED(resultD3D))
	{
		MessageBox(NULL, "CreateDevice failed", "Error", MB_OK);
		return false;
	}

	GameGlobal::SetCurrentDevice(d3ddev);

	const auto result = D3DXCreateSprite(d3ddev, &m_SpriteHandler);
	if (FAILED(result))
	{
		MessageBox(NULL, "D3DXCreateSprite failed", "Error", MB_OK);
		return false;
	}

	GameGlobal::SetCurrentSpriteHandler(m_SpriteHandler);

	return true;
}

LRESULT CALLBACK wnd_proc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;

	switch (message)
	{
		case WM_KEYDOWN:
		{
			if (wParam == VK_ESCAPE)
			{
				PostQuitMessage(0);
				DestroyWindow(hwnd);
			}
			break;
		}
		case WM_PAINT:
		{
			HDC hdc = BeginPaint(hwnd, &ps);
			EndPaint(hwnd, &ps);
			break;
		}
		case WM_CLOSE:
		{
			GameGlobal::isGameRunning = false;
			PostQuitMessage(0);
			DestroyWindow(hwnd);
			break;
		}
		default: {
			return DefWindowProc(hwnd, message, wParam, lParam);
		}
	};

	return 0;
}