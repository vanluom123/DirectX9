#include "BangerDie.h"

BangerDie::BangerDie(BangerData* banger) : BangerState(banger)
{
	Sound::GetInstance()->Play("explosions", false, 1);
	m_bangerData->banger->SetVy(Define::ENEMY_MIN_JUMP_VELOCITY);
	m_timeDie = 0;
	m_accelerateY = 25.0f;
}

Banger::eBangerState BangerDie::GetStateName()
{
	return Banger::BANGER_DIE;
}

void BangerDie::Update(float dt)
{
	m_bangerData->banger->SetVx(0);
	m_bangerData->banger->AddVy(m_accelerateY);

	m_timeDie += dt;
	if(m_timeDie >= 0.45f)
		m_bangerData->banger->SetDraw(false);
}
