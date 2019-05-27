#include "HelitAttack.h"
#include "../HelitStand/HelitStand.h"

HelitAttack::HelitAttack(HelitData* helit) :HelitState(helit)
{
	m_helitData->helit->SetVy(0);
	m_helitData->helit->SetVx(0);
	m_timeAttack = 0.0f;
	m_count = -1;
}

Helit::eHelitState HelitAttack::GetState()
{
	return Helit::HELIT_ATTACK;
}

void HelitAttack::Update(float dt)
{
	m_timeAttack += dt;
	if (m_timeAttack >= 0.4f)
	{
		m_timeAttack = 0;
		m_count++;

		if (m_count > 1)
		{
			m_helitData->helit->SetState(new HelitStand(m_helitData));
			return;
		}

		if (m_helitData->helit->GetListBullet()->size() < 2)
		{
			auto* bullet = new HelitBullet();
			m_helitData->helit->GetListBullet()->push_back(bullet);
		}

		float posX = 0;
		float posY = m_helitData->helit->GetBound().top + 35;

		if (m_helitData->helit->GetReverse())
			posX = m_helitData->helit->GetBound().right - 10;
		else
			posX = m_helitData->helit->GetBound().left + 10;


		m_helitData->helit->GetListBullet()->at(m_count)->SetPosition(posX, posY);
		m_helitData->helit->GetListBullet()->at(m_count)->SetReverse(m_helitData->helit->GetReverse());
		m_helitData->helit->GetListBullet()->at(m_count)->NewEntity();
	}
}
