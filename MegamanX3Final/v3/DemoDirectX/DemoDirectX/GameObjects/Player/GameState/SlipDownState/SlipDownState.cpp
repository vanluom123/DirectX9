#include "SlipDownState.h"
#include "../StandState/StandState.h"
#include "../FallState/FallState.h"
#include "../../../../GameDefines/GameDefine.h"


SlipDownState::SlipDownState(PlayerData* playerData) :PlayerState(playerData)
{
	m_playerData->player->SetVy(Define::PLAYER_MAX_JUMP_VELOCITY / 4);
	m_isSlide = true;
}

void SlipDownState::Update(float dt)
{
	if (!m_isSlide)
		m_playerData->player->SetState(new FallState(m_playerData));

	m_isSlide = false;
}

void SlipDownState::KeyBoardEventHandler(std::map<int, bool> keys, float dt)
{
	m_playerData->player->SetVy(Define::PLAYER_MAX_JUMP_VELOCITY / 4);
	if (keys[VK_RIGHT])
	{
		m_playerData->player->SetReverse(false);
		m_playerData->player->SetVx(Define::PLAYER_MAX_RUNNING_SPEED);
	}
	else if (keys[VK_LEFT])
	{
		m_playerData->player->SetReverse(true);
		m_playerData->player->SetVx(-Define::PLAYER_MAX_RUNNING_SPEED);
	}
	else
	{
		m_playerData->player->SetVx(0);
		m_playerData->player->SetState(new FallState(m_playerData));
	}
}

void SlipDownState::OnCollision(BaseObject::eSideCollision side)
{
	switch (side)
	{
	case BaseObject::SIDE_COLLISION_LEFT:
	case BaseObject::SIDE_COLLISION_RIGHT:
	{
		m_isSlide = true;
		break;
	}
	case BaseObject::SIDE_COLLISION_BOTTOM:
	{
		m_playerData->player->SetState(new StandState(m_playerData));
		break;
	}
	default: break;
	}
}

Player::ePlayerState SlipDownState::GetState()
{
	return Player::SLIP_DOWN;
}
