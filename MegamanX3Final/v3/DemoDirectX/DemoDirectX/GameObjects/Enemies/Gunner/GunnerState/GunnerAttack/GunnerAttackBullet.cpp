#include "GunnerAttackBullet.h"
#include "../GunnerStand/GunnerStand.h"
#include "../../../Banger/BangerBullet/BangerBullet.h"


GunnerAttackBullet::GunnerAttackBullet(GunnerData* pGunner) :GunnerState(pGunner)
{
	m_timeAttack = 0;
	m_count = 1;
}

Gunner::eGunnerState GunnerAttackBullet::GetState()
{
	return Gunner::GUNNER_ATTACK_BULLET;
}

void GunnerAttackBullet::Update(float dt)
{
	m_timeAttack += dt;
	if (m_timeAttack > 1.0f)
	{
		m_timeAttack = 0;
		m_count++;

		if (m_count > 4)
		{
			m_gunnerData->gunner->SetState(new GunnerStand(m_gunnerData));
			return;
		}

		if (m_gunnerData->gunner->GetListBullet()->size() < 5)
		{
			auto* ebullet = new BangerBullet();
			m_gunnerData->gunner->GetListBullet()->push_back(ebullet);
		}

		float posX = 0;
		float posY = m_gunnerData->gunner->GetBound().top;

		if (m_count < 5)
		{
			if (m_gunnerData->gunner->GetReverse())
				posX = m_gunnerData->gunner->GetBound().right - 16;
			else
				posX = m_gunnerData->gunner->GetBound().left + 16;
		}

		m_gunnerData->gunner->GetListBullet()->at(m_count)->SetPosition(posX, posY);
		m_gunnerData->gunner->GetListBullet()->at(m_count)->SetReverse(m_gunnerData->gunner->GetReverse());
		m_gunnerData->gunner->GetListBullet()->at(m_count)->NewEntity();
	}
}