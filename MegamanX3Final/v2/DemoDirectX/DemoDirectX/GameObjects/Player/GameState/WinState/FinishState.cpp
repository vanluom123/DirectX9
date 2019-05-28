#include "FinishState.h"

FinishState::FinishState(PLAYERDATA* playerData) :PlayerState(playerData)
{
}

Player::ePlayerState FinishState::GetState()
{
	return Player::WIN;
}
