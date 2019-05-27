#ifndef __APPEAR_STATE_H__
#define __APPEAR_STATE_H__
#include "../PlayerState.h"

class AppearState : public PlayerState
{
public:
	AppearState(PLAYERDATA* playerData);

	void update(float dt) override;

	void handlerKeyBoard(std::map<int, bool> keys, float dt) override;

	void onCollision(BaseObject::eSideCollision side) override;

	Player::StateName GetState() override;

private:
	float _accelerateY;
};

#endif
