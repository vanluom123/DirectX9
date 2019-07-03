#include "HelitStand.h"
#include "../HelitAttack/HelitAttack.h"

HelitStand::HelitStand(Helit* helit) :HelitState(helit)
{
	m_pHelit->setVx(0.0f);
	m_pHelit->setVy(-60.0f);
	_timeAttack = 0.0f;
}

HelitStand::~HelitStand()
{
}

void HelitStand::update(float dt)
{
	_timeAttack += dt;

	if (_timeAttack > 2.0f)
		m_pHelit->setState(new HelitAttack(m_pHelit));
	else
	{
		if (_timeAttack > 1.0f)
			m_pHelit->setVy(60.0f);
	}
}

Enumerator::Helit_State HelitStand::getState()
{
	return eHelit_Stand;
}
