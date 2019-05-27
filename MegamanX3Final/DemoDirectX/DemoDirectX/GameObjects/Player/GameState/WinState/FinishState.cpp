#include "FinishState.h"

FinishState::FinishState(PLAYERDATA* playerData) :PlayerState(playerData)
{
}

Player::StateName FinishState::GetState()
{
	return Player::WIN;
}
