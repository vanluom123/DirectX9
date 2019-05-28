#ifndef __GAME_TIME__
#define __GAME_TIME__

#include <Windows.h>

class GameTime
{
public:
	~GameTime();

	void StartCounter();
	void EndCounter();
	float GetCounter();
	
	static GameTime* GetInstance();

private:
	GameTime();
	static GameTime* _instance;

	LARGE_INTEGER _startTime;
	LARGE_INTEGER _endTime;
	LARGE_INTEGER _gameTime;
	LARGE_INTEGER _clockRate;
};

#endif
