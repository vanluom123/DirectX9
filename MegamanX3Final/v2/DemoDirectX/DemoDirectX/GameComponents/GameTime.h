#ifndef __GAME_TIME__
#define __GAME_TIME__

#include <Windows.h>

class GameTime
{
public:
	~GameTime();
	static GameTime* getInstance();
	static void release();

	void init();
	void resetLastTick();
	void updateGameTime();

	float getElapsedGameTime();
	float getTotalGameTime();

private:
	GameTime();
	static GameTime* _instance;

	LARGE_INTEGER _Query;
	float _freQuery;
	
	LONGLONG _startTicks;
	LONGLONG _lastTicks;
	LONGLONG _curTicks;

};

#endif
