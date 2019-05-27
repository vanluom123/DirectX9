#include "Keyboard.h"
#include "../GameDefines/GameDefine.h"


Keyboard::Keyboard(HWND hWnd)
{
	this->m_di8 = nullptr;
	this->m_did8 = nullptr;
	this->m_hWnd = hWnd;
	ZeroMemory(&this->m_keyBuffer, sizeof(this->m_keyBuffer));
}

Keyboard::~Keyboard()
{
	KillKeyBoard();
}

//Cài đặt bàn phím
bool Keyboard::Init()
{
	auto hr = DirectInput8Create(
		GetModuleHandle(nullptr),
		DIRECTINPUT_VERSION, //Tham số mặc định
		IID_IDirectInput8,
		reinterpret_cast<void**>(&this->m_di8), //Con trỏ nhận dữ liệu trả về
		nullptr); //Tham số thêm

	if (FAILED(hr))
	{
		return false;
	}
	//Tạo bàn phím GUID_SysKeyboard
	hr = this->m_di8->CreateDevice(GUID_SysKeyboard, &this->m_did8, nullptr);
	if (FAILED(hr))
	{
		return false;
	}
	//Dạng dữ liệu được nhận
	hr = this->m_did8->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(hr))
	{
		return false;
	}

	/**
	 * Loai hoat dong
	 * DISCL_FOREGROUND chỉ hoạt động khi của sổ hWnd đang được handle
	 */
	hr = this->m_did8->SetCooperativeLevel(this->m_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if (FAILED(hr))
		return false;

	//Yêu cầu thiết bị
	hr = this->m_did8->Acquire();

	return !(hr < 0);
}

//Lấy trạng thái bàn phím
void Keyboard::GetKeyState()
{
	auto hr = this->m_did8->GetDeviceState(sizeof(this->m_keyBuffer), LPVOID(&this->m_keyBuffer));
	//Nếu bàn phím nhả ra yêu cầu nhập lại
	if (FAILED(hr))
	{
		while (this->m_did8->Acquire() == DIERR_INPUTLOST);
	}
}

//Nhân diện phím nhấn
bool Keyboard::IsKeyDown(int key)
{
	//Trả về phím có được nhân hay không
	return m_keyBuffer[key] & 0x80; //0x80 xác định bit đầu tiên
}

//Kiểm tra trạng thái phím có đang down
bool Keyboard::GIsKeyDown(int key)
{
	return (IsKeyDown(key));
}

//Kiểm tra trạng thái phím có đang up
bool Keyboard::GIsKeyUp(int key)
{
	return (!(IsKeyDown(key)));
}

//Hủy phím
void Keyboard::KillKeyBoard()
{
	if(m_did8 != nullptr)
	{
		m_did8->Unacquire();
		m_did8->Release();
		m_did8 = nullptr;
	}
}
