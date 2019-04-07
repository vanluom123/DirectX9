#ifndef __CLIMB_STATE_H__
#define __CLIMB_STATE_H__
#include "../GameState.h"


class ClimbState : public GameState
{
public:
	explicit ClimbState(PlayerData* data) :GameState(data) {}
	~ClimbState() = default;
	GamePlayer::StateName GetState() override;
};

#endif
