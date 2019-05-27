#ifndef __FINISH_STATE_H__
#define __FINISH_STATE_H__
#include "../PlayerState.h"

class FinishState : public PlayerState
{
public:
	FinishState(PlayerData* playerData);
	Player::ePlayerState GetState() override;
};

#endif
