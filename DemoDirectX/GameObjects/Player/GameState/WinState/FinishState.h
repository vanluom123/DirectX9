#ifndef __FINISH_STATE_H__
#define __FINISH_STATE_H__
#include "../PlayerState.h"

class FinishState : public PlayerState
{
public:
	FinishState();
	~FinishState();
	void update(float dt) override;
	Player_State getState() override;
};

#endif
