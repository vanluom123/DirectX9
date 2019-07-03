#include "HelitAttack.h"
#include "../HelitStand/HelitStand.h"

HelitAttack::HelitAttack(Helit* helit) :HelitState(helit)
{
	m_pHelit->setVy(0.0f);
	m_pHelit->setVx(0.0f);
	_timeAttack = 0.0f;
	_count = -1;
}

HelitAttack::~HelitAttack()
{
}

Helit_State HelitAttack::getState()
{
	return eHelit_Attack;
}

void HelitAttack::update(float dt)
{
	_timeAttack += dt;
	if (_timeAttack >= 0.4f)
	{
		_timeAttack = 0.0f;
		_count++;

		if (_count > 1)
		{
			m_pHelit->setState(new HelitStand(m_pHelit));
			return;
		}

		if (m_pHelit->getListBullet()->size() < 2)
		{
			auto* bullet = new HelitBullet();
			m_pHelit->getListBullet()->push_back(bullet);
		}

		float posX = 0;
		float posY = m_pHelit->getBound().top + 35;

		if (m_pHelit->getReverse())
			posX = m_pHelit->getBound().right - 10;
		else
			posX = m_pHelit->getBound().left + 10;


		m_pHelit->getListBullet()->at(_count)->setPosition(posX, posY);
		m_pHelit->getListBullet()->at(_count)->setReverse(m_pHelit->getReverse());
		m_pHelit->getListBullet()->at(_count)->newObject();
	}
}
