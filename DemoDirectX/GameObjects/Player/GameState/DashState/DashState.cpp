#include "DashState.h"
#include <iostream>
#include "../StandState/StandState.h"
#include "../../../../GameDefines/GameDefine.h"


DashState::DashState()
{
	Sound::getInstance()->play("dash", false, 1);
	Sound::getInstance()->setVolume(95);
	this->_accelerateX = 25.0f;
	this->_timePress = 0.0f;
}

DashState::~DashState()
{ }

void DashState::KeyBoardEventHandler(std::map<int, bool> keys, float dt)
{
	Player::getInstance()->setVy(Define::PLAYER_MAX_JUMP_VELOCITY);

	this->_timePress += dt;
	if (this->_timePress <= 0.45f)
	{
		if (!Player::getInstance()->getReverse())
		{
			Player::getInstance()->setVx(Define::PLAYER_MAX_SLIDE_SPEED);
			if (keys[VK_LEFT])
				Player::getInstance()->setState(new StandState());
		}
		else
		{
			Player::getInstance()->setVx(-Define::PLAYER_MAX_SLIDE_SPEED);
			if (keys[VK_RIGHT])
				Player::getInstance()->setState(new StandState());
		}
	}
	else
		Player::getInstance()->setState(new StandState());
}

void DashState::onCollision(Side_Collision side)
{
	switch (side)
	{
		case Enumerator::Side_Collision::LEFT:
		case Enumerator::Side_Collision::RIGHT:
		{
			Sound::getInstance()->stop("dash");
			Player::getInstance()->setState(new StandState());
			break;
		}
		default: break;
	}
}

Player_State DashState::getState()
{
	return Enumerator::Player_State::DASH;
}
