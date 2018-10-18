#include "FrameWork.h"
#include <iostream>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lCmdLine, int nCmdShow)
{	
	FrameWork* frameWork = new FrameWork();

	if (frameWork->Initialize())
	{
		std::cout << "Game is created successful" << std::endl;
	}

	delete frameWork;

	return 0;
}