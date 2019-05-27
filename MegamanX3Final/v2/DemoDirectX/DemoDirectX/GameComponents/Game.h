#ifndef __GAME__
#define __GAME__
#include <d3d9.h>

#define KEYBOARD_BUFFERED_SIZE 1024

class Game
{
	float _FPS;

	//Initialize for game loop
	void InitLoop() const;

	//Function will be used to render, when it update
	static void Render();

	//Update function
	static void Update(float dt);

public:
	Game(int fps = 60);
};

#endif
