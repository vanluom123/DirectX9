#include "SlipDownState.h"
#include "../StandState/StandState.h"
#include "../FallState/FallState.h"
#include "../../../../GameDefines/GameDefine.h"


SlipDownState::SlipDownState(Player* player) :PlayerState(player)
{
	this->m_pPlayer->setVy(Define::PLAYER_MAX_JUMP_VELOCITY / 4);
	this->_isSlide = true;
}

SlipDownState::~SlipDownState()
{
}

void SlipDownState::update(float dt)
{
	if (!this->_isSlide)
		this->m_pPlayer->setState(new FallState(this->m_pPlayer));

	this->_isSlide = false;
}

void SlipDownState::KeyBoardEventHandler(map<int, bool> keys, float dt)
{
	this->m_pPlayer->setVy(Define::PLAYER_MAX_JUMP_VELOCITY / 4);
	if (keys[VK_RIGHT])
	{
		this->m_pPlayer->setReverse(false);
		this->m_pPlayer->setVx(Define::PLAYER_MAX_RUNNING_SPEED);
	}
	else if (keys[VK_LEFT])
	{
		this->m_pPlayer->setReverse(true);
		this->m_pPlayer->setVx(-Define::PLAYER_MAX_RUNNING_SPEED);
	}
	else
	{
		this->m_pPlayer->setVx(0.0f);
		this->m_pPlayer->setState(new FallState(this->m_pPlayer));
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
			this->m_pPlayer->setState(new StandState(m_pPlayer));
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
