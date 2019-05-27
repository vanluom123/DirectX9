#include "RunState.h"
#include "../StandState/StandState.h"
#include "../../../../GameDefines/GameDefine.h"


RunState::RunState(PlayerData* playerData):PlayerState(playerData)
{
}

void RunState::KeyBoardEventHandler(std::map<int, bool> keys, float dt)
{
	m_playerData->player->GetAnimation()->SetPause(false);
	m_playerData->player->SetVy(Define::PLAYER_MAX_JUMP_VELOCITY);
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
		m_playerData->player->SetState(new StandState(m_playerData));
	}
}

void RunState::OnCollision(BaseObject::eSideCollision side)
{
	switch (side)
	{
	case BaseObject::SIDE_COLLISION_LEFT:
	case BaseObject::SIDE_COLLISION_RIGHT:
		m_playerData->player->SetState(new StandState(m_playerData));
		break;
	default: break;
	}
}

Player::ePlayerState RunState::GetState()
{
	return Player::RUN;
}
