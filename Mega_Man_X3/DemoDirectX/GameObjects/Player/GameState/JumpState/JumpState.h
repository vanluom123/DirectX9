﻿#ifndef __JUMP_STATE_H__
#define __JUMP_STATE_H__
#include "../PlayerState.h"

class JumpState : public PlayerState
{
public:
	JumpState(Player* player);
	~JumpState();
	void update(float dt) override;
	void KeyBoardEventHandler(std::map<int, bool> keys, float dt) override;
	void onCollision(Side_Collision side) override;
	Player_State getState() override;

private:
	float _accelerateY;
	bool _pressed;
	float _timePress;


};
#endif