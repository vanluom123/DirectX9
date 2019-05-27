#include "DashState.h"
#include <iostream>
#include "../StandState/StandState.h"
#include "../../../../GameDefines/GameDefine.h"


DashState::DashState(PlayerData* playerData) :PlayerState(playerData)
{
	Sound::GetInstance()->Play("dash", false, 1);
	Sound::GetInstance()->SetVolume(95);
	m_accelerateX = 25.0f;
	m_timePress = 0;
}

void DashState::KeyBoardEventHandler(std::map<int, bool> keys, float dt)
{
	m_playerData->player->SetVy(Define::PLAYER_MAX_JUMP_VELOCITY);

	m_timePress += dt;
	if (m_timePress <= 0.45f)
	{
		if (!m_playerData->player->GetReverse())
		{
			m_playerData->player->SetVx(Define::PLAYER_MAX_SLIDE_SPEED);
			if (keys[VK_LEFT])
				m_playerData->player->SetState(new StandState(m_playerData));
		}
		else
		{
			m_playerData->player->SetVx(-Define::PLAYER_MAX_SLIDE_SPEED);
			if (keys[VK_RIGHT])
				m_playerData->player->SetState(new StandState(m_playerData));
		}
	}
	else
		m_playerData->player->SetState(new StandState(m_playerData));
}

void DashState::OnCollision(BaseObject::eSideCollision side)
{
	switch (side)
	{
	case BaseObject::SIDE_COLLISION_LEFT:
	case BaseObject::SIDE_COLLISION_RIGHT:
	{
		Sound::GetInstance()->Stop("dash");
		m_playerData->player->SetState(new StandState(m_playerData));
		break;
	}
	default: break;
	}
}

Player::ePlayerState DashState::GetState()
{
	return Player::DASH;
}
