#ifndef __GAME__
#define __GAME__
#include <d3d9.h>
#include "../Scenes/Scene.h"

#define KEYBOARD_BUFFERED_SIZE 1024

class Game
{
public:
	Game(int fps = 60);

private:
	float _FPS;

	//Initialize for game loop
	void initLoop();

	//Function will be used to render, when it update
	void render();

	//Update function
	void update(float dt);
};

#endif
