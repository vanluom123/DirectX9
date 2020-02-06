#include "StandState.h"
#include "../RunState/RunState.h"
#include "../../../../GameDefines/GameDefine.h"


StandState::StandState()
{
	Player::getInstance()->setVx(0.0f);
	this->_timeStand = 0.0f;
	this->_isMove = false;
}

StandState::~StandState()
{ }

void StandState::update(float dt)
{
	this->_timeStand += dt;
	if (this->_timeStand > 1.5f)
	{
		Player::getInstance()->getAnimation()->setAnimation(1, 4, 0.1f, false);
		this->_timeStand = 0.0f;
	}

	if (this->_isMove)
		Player::getInstance()->setState(new RunState());
}

void StandState::KeyBoardEventHandler(map<int, bool> keys, float dt)
{
	Player::getInstance()->setVx(0.0f);
	Player::getInstance()->setVy(Define::PLAYER_MAX_JUMP_VELOCITY);
	this->_isMove = false;

	if (keys[VK_RIGHT])
	{
		this->_isMove = true;
		Player::getInstance()->setVx(Define::PLAYER_MAX_RUNNING_SPEED);
	}
	else if (keys[VK_LEFT])
	{
		this->_isMove = true;
		Player::getInstance()->setVx(-Define::PLAYER_MAX_RUNNING_SPEED);
	}
}

void StandState::onCollision(Side_Collision side)
{
	if (side == Enumerator::Side_Collision::LEFT || side == Enumerator::Side_Collision::RIGHT)
		this->_isMove = false;
}

Player_State StandState::getState()
{
	return Enumerator::Player_State::STAND;
}
