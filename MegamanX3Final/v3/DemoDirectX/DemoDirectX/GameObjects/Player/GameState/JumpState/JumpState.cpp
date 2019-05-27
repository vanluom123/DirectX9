#include "JumpState.h"
#include "../FallState/FallState.h"
#include "../StandState/StandState.h"
#include "../SlipDownState/SlipDownState.h"
#include "../../../../GameDefines/GameDefine.h"


JumpState::JumpState(PlayerData* playerData) :PlayerState(playerData)
{
	Sound::GetInstance()->Play("JumpUp", false, 1);
	Sound::GetInstance()->SetVolume(95);

	m_playerData->player->SetVy(Define::PLAYER_MIN_JUMP_VELOCITY);
	m_accelerateY = 15.0f;
	m_timePress = 0;
	m_isPressed = false;

	if (m_playerData->state->GetState() == Player::DASH)
		m_isPressed = true;
}

void JumpState::Update(float dt)
{
	if (m_playerData->player->GetVy() > 0)
		m_playerData->player->SetState(new FallState(m_playerData, m_isPressed));
}

void JumpState::KeyBoardEventHandler(std::map<int, bool> keys, float dt)
{
	// Exception collide
	m_timePress += dt;
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
}

void JumpState::OnCollision(BaseObject::eSideCollision side)
{
	switch (side)
	{
	case BaseObject::SIDE_COLLISION_LEFT:
	case BaseObject::SIDE_COLLISION_RIGHT:
	{
		if (m_timePress < 0.3f)
			break;
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

Player::ePlayerState JumpState::GetState()
{
	return Player::JUMP;
}
