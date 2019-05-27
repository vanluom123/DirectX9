#ifndef __BLEED_STATE_H__
#define __BLEED_STATE_H__
#include "../PlayerState.h"


class BleedState : public PlayerState
{
public:
	BleedState(PlayerData* playerData, int direction);

	void Update(float dt) override;
	Player::ePlayerState GetState() override;

private:
	float m_timeBleed;

};

#endif
