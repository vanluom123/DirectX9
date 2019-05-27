#include "StandState.h"
#include "../RunState/RunState.h"
#include "../../../../GameDefines/GameDefine.h"


StandState::StandState(PlayerData* playerData) :PlayerState(playerData)
{
	m_playerData->player->SetVx(0);
	m_timeStand = 0.0f;
	m_isMove = false;
}

void StandState::Update(float dt)
{
	m_timeStand += dt;
	if (m_timeStand > 1.50f)
	{
		m_playerData->player->GetAnimation()->SetAnimation(1, 4, 0.1, false);
		m_timeStand = 0.0f;
	}

	if (m_isMove)
		m_playerData->player->SetState(new RunState(m_playerData));
}

void StandState::KeyBoardEventHandler(std::map<int, bool> keys, float dt)
{
	m_playerData->player->SetVx(0);
	m_playerData->player->SetVy(Define::PLAYER_MAX_JUMP_VELOCITY);
	m_isMove = false;

	if (keys[VK_RIGHT])
	{
		m_isMove = true;
		m_playerData->player->SetVx(Define::PLAYER_MAX_RUNNING_SPEED);
	}
	else if (keys[VK_LEFT])
	{
		m_isMove = true;
		m_playerData->player->SetVx(-Define::PLAYER_MAX_RUNNING_SPEED);
	}
}

void StandState::OnCollision(BaseObject::eSideCollision side)
{
	switch (side)
	{
	case BaseObject::SIDE_COLLISION_LEFT:
	case BaseObject::SIDE_COLLISION_RIGHT:
	{
		m_isMove = false;
	}
	default: break;
	}
}

Player::ePlayerState StandState::GetState()
{
	return Player::STAND;
}
