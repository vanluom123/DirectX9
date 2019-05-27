#include "FinishState.h"

FinishState::FinishState(PlayerData* playerData) :PlayerState(playerData)
{
}

Player::ePlayerState FinishState::GetState()
{
	return Player::WIN;
}
