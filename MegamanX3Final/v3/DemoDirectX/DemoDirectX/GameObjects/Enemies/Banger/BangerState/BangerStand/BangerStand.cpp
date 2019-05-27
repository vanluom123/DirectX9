#include "BangerStand.h"
#include "../../../../../GameDefines/GameDefine.h"
#include "../BangerAttack/BangerAttack.h"

BangerStand::BangerStand(BangerData* banger) : BangerState(banger)
{
	m_bangerData->banger->SetVx(0);
	m_bangerData->banger->SetVy(200);
	m_timePerShoot = 0.0f;
}

Banger::eBangerState BangerStand::GetStateName()
{
	return Banger::eBangerState::BANGER_STAND;
}

void BangerStand::Update(float dt)
{
	m_bangerData->banger->SetVx(0);
	m_timePerShoot += dt;
	if (m_timePerShoot > 1.0f)
		m_bangerData->banger->SetState(new BangerAttack(m_bangerData));
}
