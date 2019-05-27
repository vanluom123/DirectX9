#include  "GunnerStand.h"
#include "../GunnerAttack/GunnerAttack.h"
#include "../GunnerAttack/GunnerAttackRocket.h"
#include "../../../Banger/BangerBullet/BangerBullet.h"

GunnerStand::GunnerStand(GunnerData* headGunner) :GunnerState(headGunner)
{
	m_gunnerData->gunner->SetVx(0);
	m_gunnerData->gunner->SetVy(200);
	m_timeAttack = 0;
}

Gunner::eGunnerState GunnerStand::GetState()
{
	return Gunner::GUNNER_STAND;
}

void GunnerStand::Update(float dt)
{
	m_timeAttack += dt;
	if (m_timeAttack > 1.0f)
		m_gunnerData->gunner->SetState(new GunnerAttackRocket(m_gunnerData));
}
