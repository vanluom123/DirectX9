#ifndef __CLING_STATE_H__
#define __CLING_STATE_H__
#include "../PlayerState.h"

class ClingState : public PlayerState
{

public:
	ClingState(PLAYERDATA* playerData, bool dash = false);

	void update(float dt) override;
	void handlerKeyBoard(std::map<int, bool> keys, float dt) override;
	void onCollision(BaseObject::eSideCollision side) override;
	Player::StateName GetState() override;

private:
	float _accelerateY;
	float _speed, _countPress;
	bool _pressed;

};
#endif