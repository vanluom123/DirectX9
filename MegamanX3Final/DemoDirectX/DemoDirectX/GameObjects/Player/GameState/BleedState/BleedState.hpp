#ifndef __BLEED_STATE_H__
#define __BLEED_STATE_H__
#include "../PlayerState.h"


class BleedState : public PlayerState
{
public:
	BleedState(PLAYERDATA* playerData, int direction);

	void update(float dt) override;
	Player::StateName GetState() override;

private:
	float _timeBleed;

};

#endif
