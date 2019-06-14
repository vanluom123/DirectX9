#ifndef __CLIMB_STATE_H__
#define __CLIMB_STATE_H__
#include "../PlayerState.h"


class ClimbState : public PlayerState
{
public:
	ClimbState(PlayerData* playerData);
	Player::ePlayerState getState() override;
};

#endif
