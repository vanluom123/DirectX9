#ifndef __STAND_STATE_H__
#define __STAND_STATE_H__
#include "../PlayerState.h"

class StandState : public PlayerState
{
private:
	float _timeStand;
	bool _isMove;

public:
	StandState(Player* player);
	~StandState();
	void update(float dt) override;
	void KeyBoardEventHandler(map<int, bool> keys, float dt) override;
	void onCollision(Side_Collision side) override;
	Player_State getState() override;
};
#endif