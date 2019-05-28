#include "GameTime.h"
#include <iostream>

GameTime* GameTime::_instance = NULL;

GameTime::GameTime()
{
	std::cout << "Constructor of class GameTime" << std::endl;
}

GameTime::~GameTime()
{
	delete this;
}

void GameTime::StartCounter()
{
	QueryPerformanceFrequency(&_startTime);
	QueryPerformanceCounter(&_endTime);
}

void GameTime::EndCounter()
{
	QueryPerformanceFrequency(&_clockRate);
	QueryPerformanceCounter(&_endTime);
}

float GameTime::GetCounter()
{
	_gameTime.QuadPart = _endTime.QuadPart - _startTime.QuadPart;
	return ((float)_gameTime.QuadPart / _clockRate.QuadPart);
}

GameTime* GameTime::GetInstance()
{
	if (_instance == NULL)
		_instance = new GameTime();

	return _instance;
}
