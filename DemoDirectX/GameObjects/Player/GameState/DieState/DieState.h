#ifndef __DIE_STATE_H__
#define __DIE_STATE_H__
#include "../PlayerState.h"


class DieState : public PlayerState
{
private:
	float _timeDie;

public:
	DieState();
	~DieState();
	void update(float dt) override;
	Player_State getState() override;
};

#endif
