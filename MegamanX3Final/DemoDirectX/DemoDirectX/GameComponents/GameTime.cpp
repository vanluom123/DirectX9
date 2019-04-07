#include "GameTime.h"

GameTime::GameTime()
{
}

GameTime::~GameTime()
{
}

void GameTime::startCounter()
{
	QueryPerformanceFrequency(&startTime);
	QueryPerformanceCounter(&endTime);
}

void GameTime::endCounter()
{
	QueryPerformanceFrequency(&clockRate);
	QueryPerformanceCounter(&endTime);
}

float GameTime::getCounter()
{
	gameTime.QuadPart = endTime.QuadPart - startTime.QuadPart;
	return (float(gameTime.QuadPart) / clockRate.QuadPart);
}
