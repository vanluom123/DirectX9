#include "HelitStand.h"
#include "../HelitAttack/HelitAttack.h"

HelitStand::HelitStand(HelitData* helit) :HelitState(helit)
{
	m_helitData->helit->SetVx(0);
	m_helitData->helit->SetVy(-60);
	m_timeAttack = 0;
}

Helit::eHelitState HelitStand::GetState()
{
	return Helit::HELIT_STAND;
}

void HelitStand::Update(float dt)
{
	m_timeAttack += dt;

	if (m_timeAttack > 2.0f)
		m_helitData->helit->SetState(new HelitAttack(m_helitData));
	else
	{
		if (m_timeAttack > 1.0f)
			m_helitData->helit->SetVy(60);
	}

}
