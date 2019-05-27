#ifndef __DIE_STATE_H__
#define __DIE_STATE_H__
#include "../PlayerState.h"


class DieState : public PlayerState
{
public:
	DieState(PLAYERDATA* playerData);

	void update(float dt) override;
	Player::StateName GetState() override;

private:
	float _timeDie;

};

#endif
