#include "PlayerState.h"

PlayerState::PlayerState()
{
}

PlayerState::~PlayerState()
{
	// Do nothing
}

void PlayerState::update(float dt)
{
	// Do nothing
}

void PlayerState::KeyBoardEventHandler(map<int, bool> keys, float dt)
{
	// Do nothing
}

void PlayerState::onCollision(Side_Collision side)
{
	// Do nothing
}

Player_State PlayerState::getState()
{
	return Enumerator::Player_State::NONE;
}
