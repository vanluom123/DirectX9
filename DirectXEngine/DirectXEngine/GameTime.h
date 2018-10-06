#pragma once
#ifndef __GAME_TIME__
#define __GAME_TIME__

#include <Windows.h>


class GameTime
{
public:
	
	void StartCounter();
	float GetCounter();
	static GameTime* GetInstance();
	~GameTime() = default;

private:
	GameTime() = default;
	LARGE_INTEGER mStartTime{}, mEndTime{}, mDelta{}, mClockRate{};
	static GameTime *mInstance;
};

#endif

