#include "FrameWork.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lCmdLine, int nCmdShow)
{
	
	FrameWork* frameWork = new FrameWork();

	if (frameWork->Initialize()) {
		FrameWork::Run();
	}

	delete frameWork;

	return 0;
}