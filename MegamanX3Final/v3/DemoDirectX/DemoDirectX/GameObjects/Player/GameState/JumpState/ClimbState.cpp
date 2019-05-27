#include "ClimbState.h"

ClimbState::ClimbState(PlayerData* playerData) :PlayerState(playerData)
{
}

Player::ePlayerState ClimbState::GetState()
{
	return Player::CLIMB;
}
