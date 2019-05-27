#include "ClimbState.h"

ClimbState::ClimbState(PLAYERDATA* playerData) :PlayerState(playerData)
{
}

Player::StateName ClimbState::GetState()
{
	return Player::CLIMB;
}
