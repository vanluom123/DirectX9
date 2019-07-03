#include "SlipDownState.h"
#include "../StandState/StandState.h"
#include "../FallState/FallState.h"
#include "../../../../GameDefines/GameDefine.h"


SlipDownState::SlipDownState(Player* player) :PlayerState(player)
{
	m_pPlayer->setVy(Define::PLAYER_MAX_JUMP_VELOCITY / 4);
	_isSlide = true;
}

SlipDownState::~SlipDownState()
{
}

void SlipDownState::update(float dt)
{
	if (!_isSlide)
		m_pPlayer->setState(new FallState(m_pPlayer));

	_isSlide = false;
}

void SlipDownState::KeyBoardEventHandler(map<int, bool> keys, float dt)
{
	m_pPlayer->setVy(Define::PLAYER_MAX_JUMP_VELOCITY / 4);
	if (keys[VK_RIGHT])
	{
		m_pPlayer->setReverse(false);
		m_pPlayer->setVx(Define::PLAYER_MAX_RUNNING_SPEED);
	}
	else if (keys[VK_LEFT])
	{
		m_pPlayer->setReverse(true);
		m_pPlayer->setVx(-Define::PLAYER_MAX_RUNNING_SPEED);
	}
	else
	{
		m_pPlayer->setVx(0.0f);
		m_pPlayer->setState(new FallState(m_pPlayer));
	}
}

void SlipDownState::onCollision(Side_Collision side)
{
	switch (side)
	{
		case eSide_Left:
		case eSide_Right:
		{
			_isSlide = true;
			break;
		}
		case eSide_Bottom:
		{
			m_pPlayer->setState(new StandState(m_pPlayer));
			break;
		}
		default:
			break;
	}
}

Player_State SlipDownState::getState()
{
	return ePlayer_SlipDown;
}
