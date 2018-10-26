#ifndef __GAME__
#define __GAME__
#include <d3d9.h>

#define KEYBOARD_BUFFERED_SIZE 1024

class Game
{
	PDIRECT3DSURFACE9       mBackground,
							mBackBuffer;

	int                     mWidth,
							mHeight;
	static int              mIsDone;
	float                   mFPS;

	//Initialize for game loop
	void InitLoop();

	//Function will be used to render, when it update
	void Render();

	//Update function
	void Update(float dt);

public:
	explicit Game(int fps = 60);
    ~Game();
};

#endif