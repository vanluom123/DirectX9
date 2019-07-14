#ifndef __BLEED_STATE_H__
#define __BLEED_STATE_H__
#include "../PlayerState.h"


class BleedState : public PlayerState
{
public:
	BleedState(Player* player, int direction);
	~BleedState();
	void update(float dt) override;
	Player_State getState() override;

private:
	float _timeBleed;

};

#endif
