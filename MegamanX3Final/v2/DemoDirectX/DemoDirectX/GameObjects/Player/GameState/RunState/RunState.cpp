#include "RunState.h"
#include "../StandState/StandState.h"
#include "../../../../GameDefines/GameDefine.h"


RunState::RunState(Player* player) :PlayerState(player)
{
	_isBoot = false;
}

RunState::~RunState()
{
}

void RunState::KeyBoardEventHandler(map<int, bool> keys, float dt)
{
	m_pPlayer->getAnimation()->setPause(false);
	m_pPlayer->setVy(Define::PLAYER_MAX_JUMP_VELOCITY);
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
		m_pPlayer->setState(new StandState(m_pPlayer));
	}
}

void RunState::onCollision(Side_Collision side)
{
	switch (side)
	{
		case eSide_Left:
		case eSide_Right:
		{
			m_pPlayer->setState(new StandState(m_pPlayer));
			break;
		}
		default:
			break;
	}
}

Player_State RunState::getState()
{
	return ePlayer_Run;
}
