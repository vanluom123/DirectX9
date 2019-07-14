#include "StandState.h"
#include "../RunState/RunState.h"
#include "../../../../GameDefines/GameDefine.h"


StandState::StandState(Player* player) :PlayerState(player)
{
	m_pPlayer->setVx(0.0f);
	_timeStand = 0.0f;
	_isMove = false;
}

StandState::~StandState()
{
}

void StandState::update(float dt)
{
	_timeStand += dt;
	if (_timeStand > 1.5f)
	{
		m_pPlayer->getAnimation()->setAnimation(1, 4, 0.1f, false);
		_timeStand = 0.0f;
	}

	if (_isMove)
		m_pPlayer->setState(new RunState(m_pPlayer));
}

void StandState::KeyBoardEventHandler(map<int, bool> keys, float dt)
{
	m_pPlayer->setVx(0.0f);
	m_pPlayer->setVy(Define::PLAYER_MAX_JUMP_VELOCITY);
	_isMove = false;

	if (keys[VK_RIGHT])
	{
		_isMove = true;
		m_pPlayer->setVx(Define::PLAYER_MAX_RUNNING_SPEED);
	}
	else if (keys[VK_LEFT])
	{
		_isMove = true;
		m_pPlayer->setVx(-Define::PLAYER_MAX_RUNNING_SPEED);
	}
}

void StandState::onCollision(Side_Collision side)
{
	if (side == eSide_Left || side == eSide_Right)
		_isMove = false;
}

Player_State StandState::getState()
{
	return ePlayer_Stand;
}
