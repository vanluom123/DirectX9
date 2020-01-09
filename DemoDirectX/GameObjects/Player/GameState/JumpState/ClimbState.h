#ifndef __CLIMB_STATE_H__
#define __CLIMB_STATE_H__
#include "../PlayerState.h"


class ClimbState : public PlayerState
{
public:
	ClimbState(Player* player);
	~ClimbState();
	void update(float dt) override;
	void onCollision(Side_Collision side) override;
	void KeyBoardEventHandler(map<int, bool> keys, float dt) override;
	Player_State getState() override;

private:
	float m_timeClimb;
};

#endif
