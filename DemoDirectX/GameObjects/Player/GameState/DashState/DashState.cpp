#include "DashState.h"
#include <iostream>
#include "../StandState/StandState.h"
#include "../../../../GameDefines/GameDefine.h"


DashState::DashState(Player* player) :PlayerState(player)
{
	Sound::getInstance()->play("dash", false, 1);
	Sound::getInstance()->setVolume(95);
	this->_accelerateX = 25.0f;
	this->_timePress = 0.0f;
}

DashState::~DashState()
{
}

void DashState::KeyBoardEventHandler(std::map<int, bool> keys, float dt)
{
	this->m_pPlayer->setVy(Define::PLAYER_MAX_JUMP_VELOCITY);

	this->_timePress += dt;
	if (this->_timePress <= 0.45f)
	{
		if (!this->m_pPlayer->getReverse())
		{
			this->m_pPlayer->setVx(Define::PLAYER_MAX_SLIDE_SPEED);
			if (keys[VK_LEFT])
				this->m_pPlayer->setState(new StandState(this->m_pPlayer));
		}
		else
		{
			this->m_pPlayer->setVx(-Define::PLAYER_MAX_SLIDE_SPEED);
			if (keys[VK_RIGHT])
				this->m_pPlayer->setState(new StandState(m_pPlayer));
		}
	}
	else
		this->m_pPlayer->setState(new StandState(this->m_pPlayer));
}

void DashState::onCollision(Side_Collision side)
{
	switch (side)
	{
		case Enumerator::Side_Collision::LEFT:
		case Enumerator::Side_Collision::RIGHT:
		{
			Sound::getInstance()->stop("dash");
			this->m_pPlayer->setState(new StandState(this->m_pPlayer));
			break;
		}
		default: break;
	}
}

Player_State DashState::getState()
{
	return Enumerator::Player_State::DASH;
}
