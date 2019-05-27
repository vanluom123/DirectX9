#include "ClingState.h"
#include "../FallState/FallState.h"
#include "../StandState/StandState.h"
#include "../SlipDownState/SlipDownState.h"
#include "../../../../GameDefines/GameDefine.h"


ClingState::ClingState(PlayerData* playerData, bool dash) :PlayerState(playerData)
{
	m_speed = 0.0f;
	m_countPress = 0;
	m_playerData->player->SetVy(Define::PLAYER_MIN_JUMP_VELOCITY);
	m_accelerateY = 15.0f;

	m_isPressed = dash;
}

void ClingState::Update(float dt)
{
	if (m_playerData->player->GetVy() > 0)
		m_playerData->player->SetState(new FallState(m_playerData, m_isPressed));
}

void ClingState::KeyBoardEventHandler(std::map<int, bool> keys, float dt)
{
	m_countPress += dt;
	if (m_countPress < 0.25f)
	{
		if (m_playerData->player->GetReverse())
		{
			m_speed = Define::PLAYER_MAX_CLING_SPEED;

			if (keys[VK_RIGHT])
				m_countPress = 0.25;
		}
		else
		{
			m_speed = -Define::PLAYER_MAX_CLING_SPEED;

			if (keys[VK_LEFT])
				m_countPress = 0.25;
		}
		m_playerData->player->SetVx(m_speed);
		m_playerData->player->AddVy(m_accelerateY);
		return;
	}

	if (keys[VK_RIGHT])
	{
		m_playerData->player->SetReverse(false);

		if (m_isPressed)
			m_speed = Define::PLAYER_MAX_SLIDE_SPEED;
		else
			m_speed = Define::PLAYER_MAX_RUNNING_SPEED;
	}
	else if (keys[VK_LEFT])
	{
		m_playerData->player->SetReverse(true);
		if (m_isPressed)
			m_speed = -Define::PLAYER_MAX_SLIDE_SPEED;
		else
			m_speed = -Define::PLAYER_MAX_RUNNING_SPEED;
	}
	m_playerData->player->SetVx(m_speed);
	m_playerData->player->AddVy(m_accelerateY);
}

void ClingState::OnCollision(BaseObject::eSideCollision side)
{
	switch (side)
	{
	case BaseObject::SIDE_COLLISION_LEFT:
	case BaseObject::SIDE_COLLISION_RIGHT:
	{
		Sound::GetInstance()->Play("JumpUp", false, 1);
		Sound::GetInstance()->SetVolume(95);

		m_playerData->player->SetState(new SlipDownState(m_playerData));
		break;
	}
	case BaseObject::SIDE_COLLISION_TOP:
	{
		m_playerData->player->SetState(new FallState(m_playerData, m_isPressed));
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

Player::ePlayerState ClingState::GetState()
{
	return Player::CLING;
}
