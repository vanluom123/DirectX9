#include "SlipDownState.h"
#include "../StandState/StandState.h"
#include "../FallState/FallState.h"
#include "../../../../GameDefines/GameDefine.h"


SlipDownState::SlipDownState()
{
	Player::getInstance()->setVy(Define::PLAYER_MAX_JUMP_VELOCITY / 4);
	this->_isSlide = true;
}

SlipDownState::~SlipDownState()
{
}

void SlipDownState::update(float dt)
{
	if (!this->_isSlide)
		Player::getInstance()->setState(new FallState(Player::getInstance()));

	this->_isSlide = false;
}

void SlipDownState::KeyBoardEventHandler(map<int, bool> keys, float dt)
{
	Player::getInstance()->setVy(Define::PLAYER_MAX_JUMP_VELOCITY / 4);
	if (keys[VK_RIGHT])
	{
		Player::getInstance()->setReverse(false);
		Player::getInstance()->setVx(Define::PLAYER_MAX_RUNNING_SPEED);
	}
	else if (keys[VK_LEFT])
	{
		Player::getInstance()->setReverse(true);
		Player::getInstance()->setVx(-Define::PLAYER_MAX_RUNNING_SPEED);
	}
	else
	{
		Player::getInstance()->setVx(0.0f);
		Player::getInstance()->setState(new FallState());
	}
}

void SlipDownState::onCollision(Side_Collision side)
{
	switch (side)
	{
		case Enumerator::Side_Collision::LEFT:
		case Enumerator::Side_Collision::RIGHT:
		{
			_isSlide = true;
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

Player_State SlipDownState::getState()
{
	return Enumerator::Player_State::SLIP_DOWN;
}
