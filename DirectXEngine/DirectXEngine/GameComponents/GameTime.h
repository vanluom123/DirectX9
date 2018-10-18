#pragma once
#ifndef __GAME_TIME__
#define __GAME_TIME__

#include <Windows.h>

class GameTime
{
private:
	GameTime();
	LARGE_INTEGER mStartTime, mEndTime, mDelta, mClockRate;
	static GameTime *mInstance;

public:
    void StartCounter();
    float GetCouter();
    static GameTime* GetInstance();
    ~GameTime();

};

#endif

