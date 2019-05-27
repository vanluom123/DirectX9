#ifndef __FALL_STATE_H__
#define __FALL_STATE_H__
#include "../PlayerState.h"

class FallState : public PlayerState
{
public:
	FallState(PLAYERDATA* playerData, bool dash = false);

	void handlerKeyBoard(std::map<int, bool> keys, float dt) override;

	void onCollision(BaseObject::eSideCollision side) override;

	Player::StateName GetState() override;

private:
	float _accelerateY;
	float translateX;
	bool _pressed;
	//First Velocity equal zero in case speed won't decrease 
	bool _allowMoveX;

	bool _isLeftOrRightKeyPressed;

};
#endif
