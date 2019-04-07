#ifndef __FINISH_STATE_H__
#define __FINISH_STATE_H__
#include "../GameState.h"

class FinishState : public GameState
{
public:
	explicit FinishState(PlayerData* data) :GameState(data) {}
	~FinishState() = default;
	GamePlayer::StateName GetState() override;
};

#endif
