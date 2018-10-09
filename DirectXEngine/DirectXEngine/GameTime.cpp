#include "GameTime.h"

GameTime* GameTime::mInstance = nullptr;

GameTime* GameTime::GetInstance()
{
	if (!mInstance)
		mInstance = new GameTime();

	return mInstance;
}

GameTime::~GameTime()
{
}

GameTime::GameTime(): mStartTime(), mEndTime(), mDelta(), mClockRate()
{
}

void GameTime::StartCounter()
{
	if (!QueryPerformanceFrequency(&mClockRate))
		return;

	QueryPerformanceCounter(&mStartTime);
}

float GameTime::GetCounter()
{
	QueryPerformanceCounter(&mEndTime);
	mDelta.QuadPart = mEndTime.QuadPart - mStartTime.QuadPart;

	return (float(mDelta.QuadPart) / mClockRate.QuadPart);
}
