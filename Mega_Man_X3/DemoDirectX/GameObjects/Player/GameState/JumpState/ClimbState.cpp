#include "ClimbState.h"

ClimbState::ClimbState(Player* player) :PlayerState(player)
{
}

ClimbState::~ClimbState()
{
}

Player_State ClimbState::getState()
{
	return ePlayer_Climb;
}
