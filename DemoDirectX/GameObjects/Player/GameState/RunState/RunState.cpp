#include "RunState.h"
#include "../StandState/StandState.h"
#include "../../../../GameDefines/GameDefine.h"


RunState::RunState()
{
	this->_isBoot = false;
}

RunState::~RunState()
{
}

void RunState::KeyBoardEventHandler(map<int, bool> keys, float dt)
{
	Player::getInstance()->getAnimation()->setPause(false);

	Player::getInstance()->setVy(Define::PLAYER_MAX_JUMP_VELOCITY);
	
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
		Player::getInstance()->setState(new StandState());
	}
}

void RunState::onCollision(Side_Collision side)
{
	switch (side)
	{
		case Enumerator::Side_Collision::LEFT:
		case Enumerator::Side_Collision::RIGHT:
		{
			Player::getInstance()->setState(new StandState());
			break;
		}
		default: break;
	}
}

Player_State RunState::getState()
{
	return Enumerator::Player_State::RUN;
}
