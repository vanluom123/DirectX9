#include "FinishState.h"

FinishState::FinishState(PlayerData* playerData) :PlayerState(playerData)
{
}

Player::ePlayerState FinishState::getState()
{
	return Player::WIN;
}
