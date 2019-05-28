﻿#ifndef __STAND_STATE_H__
#define __STAND_STATE_H__
#include "../PlayerState.h"

class StandState : public PlayerState
{
private:
	float _timeStand;
	bool _isMove;

public:
	StandState(PLAYERDATA* playerData);

	void Update(float dt) override;
	void KeyBoardEventHandler(std::map<int, bool> keys, float dt) override;
	void OnCollision(BaseObject::eSideCollision side) override;
	Player::ePlayerState GetState() override;
};
#endif