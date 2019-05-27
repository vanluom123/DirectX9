#ifndef __JUMP_STATE_H__
#define __JUMP_STATE_H__
#include "../PlayerState.h"

class JumpState : public PlayerState
{
public:
	JumpState(PLAYERDATA* playerData);

	void update(float dt) override;
	void handlerKeyBoard(std::map<int, bool> keys, float dt) override;
	void onCollision(BaseObject::eSideCollision side) override;
	Player::StateName GetState() override;

protected:
	float _accelerateY;
	bool _pressed;
	float _timePress;


};
#endif