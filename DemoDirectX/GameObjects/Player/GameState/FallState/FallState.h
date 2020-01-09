#ifndef __FALL_STATE_H__
#define __FALL_STATE_H__
#include "../PlayerState.h"

class FallState : public PlayerState
{
private:
	float _accelerateY;
	float translateX;
	bool _pressed;
	//First Velocity equal zero in case speed won't decrease 
	bool _allowMoveX;

	bool _isLeftOrRightKeyPressed;

public:
	FallState(Player* player, bool dash = false);
	~FallState();
	void KeyBoardEventHandler(std::map<int, bool> keys, float dt) override;
	void onCollision(Side_Collision side) override;
	Player_State getState() override;
};
#endif
