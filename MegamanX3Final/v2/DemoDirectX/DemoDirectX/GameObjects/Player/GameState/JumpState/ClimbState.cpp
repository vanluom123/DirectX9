#include "ClimbState.h"

ClimbState::ClimbState(PLAYERDATA* playerData) :PlayerState(playerData)
{
}

Player::ePlayerState ClimbState::GetState()
{
	return Player::CLIMB;
}
