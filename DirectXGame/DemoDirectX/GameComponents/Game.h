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

	//khoi tao vong lap cho game
	void InitLoop();

	//ham dung de ve sau khi update
	void Render();

	//ham update cua game
	void Update(float dt);

public:
	explicit Game(int fps = 60);
    ~Game();
};

#endif