#include "GunnerAttack.h"
#include "../GunnerStand/GunnerStand.h"
#include "../../../Banger/BangerBullet/BangerBullet.h"
#include <iostream>
#include "GunnerAttackBullet.h"

GunnerAttack::GunnerAttack(GunnerData* headGunner) :GunnerState(headGunner)
{
	m_gunnerData->gunner->SetVx(0);
	m_gunnerData->gunner->SetVy(200);
	m_timeAttack = 0;
	m_count = 0;
}

Gunner::eGunnerState GunnerAttack::GetState()
{
	return Gunner::GUNNER_ATTACK;
}

void GunnerAttack::Update(float dt)
{
	m_timeAttack += dt;
	if (m_timeAttack >= 0.45f)
	{
		m_timeAttack = 0;
		m_count++;

		if (m_count > 1)
		{
			m_gunnerData->gunner->SetState(new GunnerAttackBullet(m_gunnerData));
			return;
		}

		if (m_gunnerData->gunner->GetListBullet()->size() < 3)
		{
			if (m_count == 1)
			{
				auto* ebullet = new GunnerBullet();
				m_gunnerData->gunner->GetListBullet()->push_back(ebullet);
			}
			
		}

		float posX = 0;
		float posY = m_gunnerData->gunner->GetBound().top;

		if (m_count == 1)
		{
			posY += 17;
			if (m_gunnerData->gunner->GetReverse())
				posX = m_gunnerData->gunner->GetBound().right;
			else
				posX = m_gunnerData->gunner->GetBound().left;
		}

		m_gunnerData->gunner->GetListBullet()->at(m_count)->SetPosition(posX, posY);
		m_gunnerData->gunner->GetListBullet()->at(m_count)->SetReverse(m_gunnerData->gunner->GetReverse());
		m_gunnerData->gunner->GetListBullet()->at(m_count)->NewEntity();
	}
}