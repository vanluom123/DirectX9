#include "FallState.h"
#include "../RunState/RunState.h"
#include "../StandState/StandState.h"
#include "../SlipDownState/SlipDownState.h"
#include "../../../../GameDefines/GameDefine.h"


FallState::FallState(bool dash)
{
	Player::getInstance()->setVy(0.0f);
	this->_accelerateY = 25.0f;
	this->_pressed = dash;
}

FallState::~FallState()
{
}

void FallState::KeyBoardEventHandler(std::map<int, bool> keys, float dt)
{
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

	if (Player::getInstance()->getVy() > Define::PLAYER_MAX_JUMP_VELOCITY)
		Player::getInstance()->setVy(Define::PLAYER_MAX_JUMP_VELOCITY);
}

void FallState::onCollision(Side_Collision side)
{
	switch (side)
	{
		case Enumerator::Side_Collision::LEFT:
		case Enumerator::Side_Collision::RIGHT:
		{
			Player::getInstance()->setState(new SlipDownState());
			break;
		}
		case Enumerator::Side_Collision::BOTTOM:
		{
			Sound::getInstance()->play("FallDownGround", false, 1);
			Sound::getInstance()->setVolume(95);
			Player::getInstance()->setState(new StandState());
			break;
		}
		default:
			break;
	}
}

Player_State FallState::getState()
{
	return Enumerator::Player_State::FALL;
}
