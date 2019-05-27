#include "DieState.h"


DieState::DieState(PlayerData* playerData) : PlayerState(playerData)
{
	m_playerData->player->SetVx(0);
	m_playerData->player->SetVy(0);
	m_timeDie = 0.0f;
}

void DieState::Update(float dt)
{
	m_timeDie += dt;

	Sound::GetInstance()->Play("RockmanDie", false, m_timeDie);
	Sound::GetInstance()->SetVolume(95);

	if (m_timeDie >= 3.0f)
	{
		m_playerData->player->GetAnimation()->SetAnimation(20, 3, 0.3);
		m_playerData->player->SetDraw(false);
	}
}

Player::ePlayerState DieState::GetState()
{
	return Player::DIE;
}
