#ifndef __GAME__
#define __GAME__
#include <d3d9.h>

#define KEYBOARD_BUFFERED_SIZE 1024

class Game
{
public:
	explicit Game(int fps = 60);

	// Initialize game loop
	void InitLoop();

	~Game();

protected:

	PDIRECT3DSURFACE9       mBackground,
							mBackBuffer;

	int                     mWidth,
							mHeight;

	static int              mIsDone;
	float                   mFPS;

	// Function used to draw when updated
	static void Render();
	// Function update game
	static void Update(float dt);
};

#endif