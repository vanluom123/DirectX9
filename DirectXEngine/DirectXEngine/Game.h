#ifndef __GAME__
#define __GAME__
#include <d3d9.h>

#define KEYBOARD_BUFFERD_SIZE 1024

class Game
{
public:
	Game(int fps = 60);

	~Game() = default;

protected:

	PDIRECT3DSURFACE9       mBackground{},
							mBackBuffer{};

	int                     mWidth{},
							mHeight{};

	static int              mIsDone;
	float                   mFPS;

	//khoi tao vong lap cho game
	void InitLoop() const;

	//ham dung de ve sau khi update
	static void Render();

	//ham update cua game
	static void Update(float dt);
};

#endif