#include "FallState.h"
#include "../RunState/RunState.h"
#include "../StandState/StandState.h"
#include "../SlipDownState/SlipDownState.h"
#include "../../../../GameDefines/GameDefine.h"


FallState::FallState(PlayerData* playerData, bool dash) :PlayerState(playerData)
{
	m_playerData->player->SetVy(0);
	m_accelerateY = 25.0f;
	m_isPressed = dash;
}

void FallState::KeyBoardEventHandler(std::map<int, bool> keys, float dt)
{
	float speed = 0.0f;
	if (keys[VK_RIGHT])
	{
		m_playerData->player->SetReverse(false);

		if (m_isPressed)
			speed = Define::PLAYER_MAX_SLIDE_SPEED;
		else
			speed = Define::PLAYER_MAX_RUNNING_SPEED;
	}
	else if (keys[VK_LEFT])
	{
		m_playerData->player->SetReverse(true);
		if (m_isPressed)
			speed = -Define::PLAYER_MAX_SLIDE_SPEED;
		else
			speed = -Define::PLAYER_MAX_RUNNING_SPEED;
	}
	m_playerData->player->SetVx(speed);

	m_playerData->player->AddVy(m_accelerateY);

	if (m_playerData->player->GetVy() > Define::PLAYER_MAX_JUMP_VELOCITY)
		m_playerData->player->SetVy(Define::PLAYER_MAX_JUMP_VELOCITY);
}

void FallState::OnCollision(BaseObject::eSideCollision side)
{
	switch (side)
	{
	case BaseObject::SIDE_COLLISION_LEFT:
	case BaseObject::SIDE_COLLISION_RIGHT:
	{
		m_playerData->player->SetState(new SlipDownState(m_playerData));
		break;
	}
	case BaseObject::SIDE_COLLISION_BOTTOM:
	{
		Sound::GetInstance()->Play("FallDownGround", false, 1);
		Sound::GetInstance()->SetVolume(95);
		m_playerData->player->SetState(new StandState(m_playerData));
		break;
	}
	default: break;
	}
}

Player::ePlayerState FallState::GetState()
{
	return Player::FALL;
}
