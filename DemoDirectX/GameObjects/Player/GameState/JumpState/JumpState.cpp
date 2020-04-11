﻿#include "JumpState.h"
#include "../FallState/FallState.h"
#include "../StandState/StandState.h"
#include "../SlipDownState/SlipDownState.h"
#include "../../../../GameDefines/GameDefine.h"


JumpState::JumpState()
{
	Sound::getInstance()->play("JumpUp", false, 1);
	Sound::getInstance()->setVolume(95);

	Player::getInstance()->setVy(Define::PLAYER_MIN_JUMP_VELOCITY);
	this->_accelerateY = 15.0f;
	this->_timePress = 0;
	this->_pressed = false;

	if (Player::getInstance()->getPlayerState()->getState() == Enumerator::Player_State::DASH)
		this->_pressed = true;
}

JumpState::~JumpState()
{
}

void JumpState::update(float dt)
{
	if (Player::getInstance()->getVy() > 0)
		Player::getInstance()->setState(new FallState(this->_pressed));
}

void JumpState::KeyBoardEventHandler(std::map<int, bool> keys, float dt)
{
	// Exception collide
	this->_timePress += dt;
	float speed = 0.0f;

	if (keys[VK_RIGHT])
	{
		Player::getInstance()->setReverse(false);

		if (this->_pressed)
			speed = Define::PLAYER_MAX_SLIDE_SPEED;
		else
			speed = Define::PLAYER_MAX_RUNNING_SPEED;
	}
	else if (keys[VK_LEFT])
	{
		Player::getInstance()->setReverse(true);
		if (this->_pressed)
			speed = -Define::PLAYER_MAX_SLIDE_SPEED;
		else
			speed = -Define::PLAYER_MAX_RUNNING_SPEED;
	}

	Player::getInstance()->setVx(speed);
	Player::getInstance()->addVy(_accelerateY);
}

void JumpState::onCollision(Side_Collision side)
{
	switch (side)
	{
		case Enumerator::Side_Collision::LEFT:
		case Enumerator::Side_Collision::RIGHT:
		{
			if (this->_timePress < 0.3f)
				break;
			Player::getInstance()->setState(new SlipDownState());
			break;
		}
		case Enumerator::Side_Collision::TOP:
		{
			Player::getInstance()->setState(new FallState(this->_pressed));
			break;
		}
		case Enumerator::Side_Collision::BOTTOM:
		{
			Player::getInstance()->setState(new StandState());
			break;
		}
		default:
			break;
	}
}

Player_State JumpState::getState()
{
	return Enumerator::Player_State::JUMP;
}