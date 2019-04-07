#ifndef __BLEED_STATE_H__
#define __BLEED_STATE_H__
#include "../GameState.h"


class BleedState : public GameState
{
public:
	explicit BleedState(PlayerData* data, int Direction);
	~BleedState() = default;

	void update(float dt) override;
	GamePlayer::StateName GetState() override;

protected:
	float timeBleed;

};

#endif
