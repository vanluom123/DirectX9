#include "AppearState.h"
#include "../StandState/StandState.h"
#include "../../../../GameDefines/GameDefine.h"


AppearState::AppearState(PlayerData* playerData) : PlayerState(playerData)
{
	m_accelerateY = 25.0f;
}

void AppearState::Update(float dt)
{
	if (m_playerData->player->GetAnimation()->GetCurrentColumn() == 0)
		m_playerData->player->GetAnimation()->SetPause(true);
	else if (m_playerData->player->GetAnimation()->GetCurrentColumn() >= 4)
		m_playerData->player->SetState(new StandState(m_playerData));
}

void AppearState::KeyBoardEventHandler(std::map<int, bool> keys, float dt)
{
	m_playerData->player->SetVx(0);
	m_playerData->player->AddVy(m_accelerateY);

	if (m_playerData->player->GetVy() > Define::PLAYER_MAX_JUMP_VELOCITY)
		m_playerData->player->SetVy(Define::PLAYER_MAX_JUMP_VELOCITY);
}

void AppearState::OnCollision(BaseObject::eSideCollision side)
{
	switch (side)
	{
	case BaseObject::SIDE_COLLISION_BOTTOM:
		m_playerData->player->GetAnimation()->SetPause(false);
		break;

	default: break;
	}
}

Player::ePlayerState AppearState::GetState()
{
	return Player::APPEAR;
}
