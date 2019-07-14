#include "DashState.h"
#include <iostream>
#include "../StandState/StandState.h"
#include "../../../../GameDefines/GameDefine.h"


DashState::DashState(Player* player) :PlayerState(player)
{
	Sound::getInstance()->play("dash", false, 1);
	Sound::getInstance()->setVolume(95);
	_accelerateX = 25.0f;
	_timePress = 0.0f;
}

DashState::~DashState()
{
}

void DashState::KeyBoardEventHandler(std::map<int, bool> keys, float dt)
{
	m_pPlayer->setVy(Define::PLAYER_MAX_JUMP_VELOCITY);

	_timePress += dt;
	if (_timePress <= 0.45f)
	{
		if (!m_pPlayer->getReverse())
		{
			m_pPlayer->setVx(Define::PLAYER_MAX_SLIDE_SPEED);
			if (keys[VK_LEFT])
				m_pPlayer->setState(new StandState(m_pPlayer));
		}
		else
		{
			m_pPlayer->setVx(-Define::PLAYER_MAX_SLIDE_SPEED);
			if (keys[VK_RIGHT])
				m_pPlayer->setState(new StandState(m_pPlayer));
		}
	}
	else
		m_pPlayer->setState(new StandState(m_pPlayer));
}

void DashState::onCollision(Side_Collision side)
{
	switch (side)
	{
		case eSide_Left:
		case eSide_Right:
		{
			Sound::getInstance()->stop("dash");
			m_pPlayer->setState(new StandState(m_pPlayer));
			break;
		}
		default: break;
	}
}

Player_State DashState::getState()
{
	return ePlayer_Dash;
}
