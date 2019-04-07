#ifndef __GAME_TIME__
#define __GAME_TIME__

#include <Windows.h>

class GameTime
{
protected:
	GameTime();
	~GameTime();

	LARGE_INTEGER startTime, endTime, gameTime, clockRate;

public:
	
	void startCounter();
	void endCounter();
	float getCounter();

	static GameTime& Instance()
	{
		static GameTime instance;
		return instance;
	}
};

#endif
