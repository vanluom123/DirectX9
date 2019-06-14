#ifndef __DIE_STATE_H__
#define __DIE_STATE_H__
#include "../PlayerState.h"


class DieState : public PlayerState
{
public:
	DieState(PlayerData* playerData);

	void Update(float dt) override;
	Player::ePlayerState getState() override;

private:
	float _timeDie;

};

#endif
