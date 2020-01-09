#include "RunState.h"
#include "../StandState/StandState.h"
#include "../../../../GameDefines/GameDefine.h"


RunState::RunState(Player* player) :PlayerState(player)
{
	this->_isBoot = false;
}

RunState::~RunState()
{
}

void RunState::KeyBoardEventHandler(map<int, bool> keys, float dt)
{
	this->m_pPlayer->getAnimation()->setPause(false);

	this->m_pPlayer->setVy(Define::PLAYER_MAX_JUMP_VELOCITY);
	
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
		this->m_pPlayer->setState(new StandState(this->m_pPlayer));
	}
}

void RunState::onCollision(Side_Collision side)
{
	switch (side)
	{
		case Enumerator::Side_Collision::LEFT:
		case Enumerator::Side_Collision::RIGHT:
		{
			this->m_pPlayer->setState(new StandState(this->m_pPlayer));
			break;
		}
		default: break;
	}
}

Player_State RunState::getState()
{
	return Enumerator::Player_State::RUN;
}
