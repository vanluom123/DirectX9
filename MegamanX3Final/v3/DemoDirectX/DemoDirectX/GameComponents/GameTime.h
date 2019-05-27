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
	static GameTime* m_instance;

	LARGE_INTEGER m_startTime;
	LARGE_INTEGER m_endTime;
	LARGE_INTEGER m_gameTime;
	LARGE_INTEGER m_clockRate;
};

#endif
