﻿#ifndef __DASH_STATE_H__
#define __DASH_STATE_H__
#include "../PlayerState.h"

class DashState : public PlayerState
{
public:
	DashState(Player* player);
	~DashState();
	void KeyBoardEventHandler(map<int, bool> keys, float dt) override;
	void onCollision(Side_Collision side) override;
	Player_State getState() override;

private:
	float _accelerateX;
	float _timePress;

};
#endif