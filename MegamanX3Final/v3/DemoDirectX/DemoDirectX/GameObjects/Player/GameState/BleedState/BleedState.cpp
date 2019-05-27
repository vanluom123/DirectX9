#include "BleedState.hpp"
#include "../StandState/StandState.h"


BleedState::BleedState(PlayerData* playerData, int direction) : PlayerState(playerData)
{
	m_playerData->player->SetVx(30.0f * direction);
	m_playerData->player->SetVy(5.0f);
	m_timeBleed = 0.0f;
}

void BleedState::Update(float dt)
{
	m_playerData->player->SetVx(0);
	m_playerData->player->GetAnimation()->SetPause(false);

	if (m_playerData->player->GetAnimation()->GetCurrentColumn() >= 8)
		m_playerData->player->SetState(new StandState(m_playerData));
}

Player::ePlayerState BleedState::GetState()
{
	return Player::BLEED;
}
