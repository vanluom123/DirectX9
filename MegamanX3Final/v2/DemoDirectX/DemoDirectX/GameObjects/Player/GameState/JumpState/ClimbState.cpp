#include "ClimbState.h"

ClimbState::ClimbState(PlayerData* playerData) :PlayerState(playerData)
{
}

Player::ePlayerState ClimbState::getState()
{
	return Player::CLIMB;
}
