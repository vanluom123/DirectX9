#include "PlayerState.h"

PlayerState::PlayerState(Player * player)
{
	m_pPlayer = player;
}

PlayerState::~PlayerState()
{
}

void PlayerState::update(float dt)
{
}

void PlayerState::KeyBoardEventHandler(map<int, bool> keys, float dt)
{
}

void PlayerState::onCollision(Side_Collision side)
{
}

Player_State PlayerState::getState()
{
	return Player_State();
}
