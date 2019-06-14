#include "GameTime.h"

GameTime* GameTime::_instance = nullptr;

GameTime* GameTime::getInstance()
{
	if (_instance == nullptr)
		_instance = new GameTime();
	return _instance;
}

void GameTime::release()
{
	delete _instance;
	_instance = nullptr;
}

void GameTime::init()
{
	QueryPerformanceFrequency(&this->_Query);

	this->_freQuery = (float)_Query.QuadPart / 10000000;
	QueryPerformanceCounter(&_Query);
	_startTicks = _lastTicks = _Query.QuadPart;
}

void GameTime::resetLastTick()
{
	_lastTicks = 0;
	_curTicks = 0;
}

void GameTime::updateGameTime()
{
	QueryPerformanceCounter(&_Query);
	_curTicks = _Query.QuadPart;
	if ((UINT64)((float)(_curTicks - _lastTicks) / _freQuery))
		return;
	auto gt = ((float)(_curTicks - _lastTicks)) / _freQuery;
	_lastTicks = _curTicks;
}

float GameTime::getElapsedGameTime()
{
	return 0.0f;
}

float GameTime::getTotalGameTime()
{
	return 0.0f;
}
