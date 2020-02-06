#include "ClingState.h"
#include "../FallState/FallState.h"
#include "../StandState/StandState.h"
#include "../SlipDownState/SlipDownState.h"
#include "../../../../GameDefines/GameDefine.h"


ClingState::ClingState(bool dash)
{
	this->_speed = 0.0f;
	this->_countPress = 0.0f;
	Player::getInstance()->setVy(Define::PLAYER_MIN_JUMP_VELOCITY);
	this->_accelerateY = 15.0f;

	this->_pressed = dash;
}

ClingState::~ClingState()
{
	// Do nothing
}

void ClingState::update(float dt)
{
	if (Player::getInstance()->getVy() > 0)
		Player::getInstance()->setState(new FallState(this->_pressed));
}

void ClingState::KeyBoardEventHandler(std::map<int, bool> keys, float dt)
{
	this->_countPress += dt;
	if (this->_countPress < 0.25f)
	{
		if (Player::getInstance()->getReverse())
		{
			this->_speed = Define::PLAYER_MAX_CLING_SPEED;

			if (keys[VK_RIGHT])
				this->_countPress = 0.25;
		}
		else
		{
			this->_speed = -Define::PLAYER_MAX_CLING_SPEED;

			if (keys[VK_LEFT])
				this->_countPress = 0.25;
		}
		Player::getInstance()->setVx(this->_speed);
		Player::getInstance()->addVy(this->_accelerateY);
		return;
	}

	if (keys[VK_RIGHT])
	{
		Player::getInstance()->setReverse(false);

		if (this->_pressed)
			this->_speed = Define::PLAYER_MAX_SLIDE_SPEED;
		else
			this->_speed = Define::PLAYER_MAX_RUNNING_SPEED;
	}
	else if (keys[VK_LEFT])
	{
		Player::getInstance()->setReverse(true);
		if (this->_pressed)
			this->_speed = -Define::PLAYER_MAX_SLIDE_SPEED;
		else
			this->_speed = -Define::PLAYER_MAX_RUNNING_SPEED;
	}
	Player::getInstance()->setVx(this->_speed);
	Player::getInstance()->addVy(this->_accelerateY);
}

void ClingState::onCollision(Side_Collision side)
{
	switch (side)
	{
		case Enumerator::Side_Collision::LEFT:
		case Enumerator::Side_Collision::RIGHT:
		{
			Sound::getInstance()->play("JumpUp", false, 1);
			Sound::getInstance()->setVolume(95);

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
		default: break;
	}
}

Player_State ClingState::getState()
{
	return Enumerator::Player_State::CLING;
}
