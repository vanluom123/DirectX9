#ifndef __STAND_STATE_H__
#define __STAND_STATE_H__
#include "../PlayerState.h"

class StandState : public PlayerState
{
private:
	float _timeStand;
	bool _isMove;

public:
	StandState(PLAYERDATA* playerData);

	void update(float dt) override;
	void handlerKeyBoard(std::map<int, bool> keys, float dt) override;
	void onCollision(BaseObject::eSideCollision side) override;
	Player::StateName GetState() override;
};
#endif