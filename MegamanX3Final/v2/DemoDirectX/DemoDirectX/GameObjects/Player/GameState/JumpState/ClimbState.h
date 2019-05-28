#ifndef __CLIMB_STATE_H__
#define __CLIMB_STATE_H__
#include "../PlayerState.h"


class ClimbState : public PlayerState
{
public:
	ClimbState(PLAYERDATA* playerData);
	Player::ePlayerState GetState() override;
};

#endif
