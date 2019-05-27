#pragma once
#include <dinput.h>

class Keyboard
{
public:
	Keyboard(HWND);
	~Keyboard();

	bool Init();					//Cài đặt bàn phím
	void GetKeyState();				//Lấy trạng thái bàn phím
	bool IsKeyDown(int key);		//Nhận diện phím nhấn
	bool GIsKeyDown(int key);		//Kiểm tra trạng thái phím có đang down
	bool GIsKeyUp(int key);			//Kiểm tra trạng thái phím có đang up
	void KillKeyBoard();			//Hủy phím

private:

	LPDIRECTINPUT8 m_di8;				//Đối tượng nhập xuất
	LPDIRECTINPUTDEVICE8 m_did8;		//Thiết bị nhập xuất
	char m_keyBuffer[256];			//Buffer lưu dữ liệu lấy từ thiết bị

	//Display programming
	//Drawing windows handler
	HWND m_hWnd;
};
