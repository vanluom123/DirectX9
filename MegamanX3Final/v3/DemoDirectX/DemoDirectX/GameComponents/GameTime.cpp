#include "GameTime.h"
#include <iostream>

GameTime* GameTime::m_instance = NULL;

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
	QueryPerformanceFrequency(&m_startTime);
	QueryPerformanceCounter(&m_endTime);
}

void GameTime::EndCounter()
{
	QueryPerformanceFrequency(&m_clockRate);
	QueryPerformanceCounter(&m_endTime);
}

float GameTime::GetCounter()
{
	m_gameTime.QuadPart = m_endTime.QuadPart - m_startTime.QuadPart;
	return ((float)m_gameTime.QuadPart / m_clockRate.QuadPart);
}

GameTime* GameTime::GetInstance()
{
	if (m_instance == NULL)
		m_instance = new GameTime();

	return m_instance;
}
