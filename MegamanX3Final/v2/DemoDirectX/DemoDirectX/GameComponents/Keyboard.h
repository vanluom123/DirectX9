#pragma once

#define DIRECTINPUT_VERSION  0x0800
#include <dinput.h>

class Keyboard
{
public:
	Keyboard(HWND);
	~Keyboard();

	bool createKeyboard();					//Cài đặt bàn phím
	void getKeyState();				//Lấy trạng thái bàn phím
	bool isKeyDown(int key);		//Nhận diện phím nhấn
	bool gIsKeyDown(int key);		//Kiểm tra trạng thái phím có đang down
	bool gIsKeyUp(int key);			//Kiểm tra trạng thái phím có đang up
	void releaseKeyboard();			//Hủy phím

private:

	LPDIRECTINPUT8 Di8;				//Đối tượng nhập xuất
	LPDIRECTINPUTDEVICE8 DiD8;		//Thiết bị nhập xuất
	char key_buffer[256];			//Buffer lưu dữ liệu lấy từ thiết bị

	//Display programming
	//Drawing windows handler
	HWND _hWnd;
};
