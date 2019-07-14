#include "FinishState.h"

FinishState::FinishState(Player* player) :PlayerState(player)
{
}

FinishState::~FinishState()
{
}

Player_State FinishState::getState()
{
	return ePlayer_Win;
}
