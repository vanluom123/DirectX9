#include "GunnerAttackRocket.h"
#include "GunnerAttack.h"

GunnerAttackRocket::GunnerAttackRocket(GunnerData* pGunner) :GunnerState(pGunner)
{
	pGunner->gunner->SetVy(200);
	pGunner->gunner->SetVx(0);
	m_timeAttack = 0;
	m_count = -1;
}

Gunner::eGunnerState GunnerAttackRocket::GetState()
{
	return Gunner::GUNNER_ATTACK_ROCKET;
}

void GunnerAttackRocket::Update(float dt)
{
	m_timeAttack += dt;
	if (m_timeAttack >= 0.45f)
	{
		m_timeAttack = 0;
		m_count++;

		if (m_count > 0)
		{
			m_gunnerData->gunner->SetState(new GunnerAttack(m_gunnerData));
			return;
		}

		if(m_gunnerData->gunner->GetListBullet()->empty())
		{
			auto* ebullet = new GunnerBullet();
			m_gunnerData->gunner->GetListBullet()->push_back(ebullet);
		}

		float posX = 0;
		float posY = m_gunnerData->gunner->GetBound().top + 12;

		if (m_count == 0)
		{
			if (m_gunnerData->gunner->GetReverse())
				posX = m_gunnerData->gunner->GetBound().right - 10;
			else
				posX = m_gunnerData->gunner->GetBound().left + 10;
		}

		m_gunnerData->gunner->GetListBullet()->at(m_count)->SetPosition(posX, posY);
		m_gunnerData->gunner->GetListBullet()->at(m_count)->SetReverse(m_gunnerData->gunner->GetReverse());
		m_gunnerData->gunner->GetListBullet()->at(m_count)->NewEntity();
	}
}