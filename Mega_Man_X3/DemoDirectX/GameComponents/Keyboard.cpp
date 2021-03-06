﻿#include "Keyboard.h"
#include "../GameDefines/GameDefine.h"


Keyboard::Keyboard(HWND hWnd)
{
	this->Di8 = nullptr;
	this->DiD8 = nullptr;
	this->_hWnd = hWnd;
	ZeroMemory(&this->key_buffer, sizeof(this->key_buffer));
}

Keyboard::~Keyboard()
{
	releaseKeyboard();
}

//Cài đặt bàn phím
bool Keyboard::createKeyboard()
{
	auto hr = DirectInput8Create(
		GetModuleHandle(nullptr),
		DIRECTINPUT_VERSION, //Tham số mặc định
		IID_IDirectInput8,
		reinterpret_cast<void**>(&this->Di8), //Con trỏ nhận dữ liệu trả về
		nullptr); //Tham số thêm

	if (FAILED(hr))
	{
		return false;
	}

	//Tạo bàn phím GUID_SysKeyboard
	hr = this->Di8->CreateDevice(GUID_SysKeyboard, &this->DiD8, nullptr);
	if (FAILED(hr))
	{
		return false;
	}

	//Dạng dữ liệu được nhận
	hr = this->DiD8->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(hr))
	{
		return false;
	}

	/**
	 * Loai hoat dong
	 * DISCL_FOREGROUND chỉ hoạt động khi của sổ hWnd đang được handle
	 */
	hr = this->DiD8->SetCooperativeLevel(this->_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if (FAILED(hr))
		return false;

	//Yêu cầu thiết bị
	hr = this->DiD8->Acquire();
	if (FAILED(hr))
		return false;

	return true;
}

//Lấy trạng thái bàn phím
void Keyboard::getKeyState()
{
	auto hr = this->DiD8->GetDeviceState(sizeof(this->key_buffer), LPVOID(&this->key_buffer));
	//Nếu bàn phím nhả ra yêu cầu nhập lại
	if (FAILED(hr))
	{
		while (this->DiD8->Acquire() == DIERR_INPUTLOST);
	}
}

//Nhân diện phím nhấn
bool Keyboard::isKeyDown(int key)
{
	//Trả về phím có được nhân hay không
	return key_buffer[key] & 0x80; //0x80 xác định bit đầu tiên
}

//Kiểm tra trạng thái phím có đang down
bool Keyboard::gIsKeyDown(int key)
{
	return (isKeyDown(key));
}

//Kiểm tra trạng thái phím có đang up
bool Keyboard::gIsKeyUp(int key)
{
	return (!(isKeyDown(key)));
}

//Hủy phím
void Keyboard::releaseKeyboard()
{
	if(DiD8 != nullptr)
	{
		DiD8->Unacquire();
		DiD8->Release();
		DiD8 = nullptr;
	}
}
