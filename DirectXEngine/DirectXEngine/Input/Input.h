#ifndef _INPUT_H
#define _INPUT_H

#include <dinput.h>

class Input {

	char keys[256];

	LPDIRECTINPUT8 m_Input;

	LPDIRECTINPUTDEVICE8 m_InputDevice;

	LPDIRECTINPUTDEVICE8 m_Keyboard;

	LPDIRECTINPUTDEVICE8 m_Mouse;

	DIMOUSESTATE m_MouseState;


public:

	Input();
	~Input();

	bool CreateInputDevice(HWND hWnd);
	bool CreateKeyboard(HWND hWnd);
	bool CreateMouse(HWND hWnd);

	bool ReadKeyboard();
	void ReleaseKeyboard();
	int Key_Down(int keyCode);

	bool ReadMouse();
	void ReleaseMouse();

	int Mouse_Button(int keyCode);
	int Mouse_X();
	int Mouse_Y();
};

#endif