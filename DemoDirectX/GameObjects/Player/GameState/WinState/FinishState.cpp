#include "FinishState.h"

FinishState::FinishState()
{
	// Do something
}

FinishState::~FinishState()
{
	// Do something
}

void FinishState::update(float dt)
{
	// Do something
}

Player_State FinishState::getState()
{
	return Enumerator::Player_State::WIN;
}
