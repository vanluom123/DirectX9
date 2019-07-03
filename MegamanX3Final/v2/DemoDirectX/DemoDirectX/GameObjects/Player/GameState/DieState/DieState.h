#ifndef __DIE_STATE_H__
#define __DIE_STATE_H__
#include "../PlayerState.h"


class DieState : public PlayerState
{
public:
	DieState(Player* player);
	~DieState();
	void update(float dt) override;
	Player_State getState() override;

private:
	float _timeDie;

};

#endif
