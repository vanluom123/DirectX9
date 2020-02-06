#include "ClimbState.h"

ClimbState::ClimbState()
{
	this->m_timeClimb = 0.0f;
}

ClimbState::~ClimbState()
{
	// Do something
}

void ClimbState::update(float dt)
{
	// Do something
	this->m_timeClimb += dt;
}

void ClimbState::onCollision(Side_Collision side)
{
	// Do something
}

void ClimbState::KeyBoardEventHandler(map<int, bool> keys, float dt)
{
	// 1. Jump up collision with object stairs
	// 2. Run down collision with object stairs
	// if(player->stand_up_stairs())
	// then if(keys[VK_DOWN] is pressed)
	// then vy += accelerateY; player->setStatus(new Climb(player));
}

Player_State ClimbState::getState()
{
	return Enumerator::Player_State::CLIMB;
}
