#include "GunnerAttackRocket.h"
#include "GunnerAttack.h"

GunnerAttackRocket::GunnerAttackRocket(Gunner* pGunner) :GunnerState(pGunner)
{
	m_pGunner->setVy(200);
	m_pGunner->setVx(0);
	_timeAttack = 0;
	_count = -1;
}

GunnerAttackRocket::~GunnerAttackRocket()
{
}

void GunnerAttackRocket::Update(float dt)
{
	_timeAttack += dt;
	if (_timeAttack >= 0.45f)
	{
		_timeAttack = 0;
		_count++;

		if (_count > 0)
		{
			m_pGunner->setState(new GunnerAttack(m_pGunner));
			return;
		}

		if(m_pGunner->getListBullet()->empty())
		{
			auto ebullet = new GunnerBullet();
			m_pGunner->getListBullet()->push_back(ebullet);
		}

		float posX = 0;
		float posY = m_pGunner->getBound().top + 12;

		if (_count == 0)
		{
			if (m_pGunner->getReverse())
				posX = m_pGunner->getBound().right - 10;
			else
				posX = m_pGunner->getBound().left + 10;
		}

		m_pGunner->getListBullet()->at(_count)->setPosition(posX, posY);
		m_pGunner->getListBullet()->at(_count)->setReverse(m_pGunner->getReverse());
		m_pGunner->getListBullet()->at(_count)->newObject();
	}
}

Enumerator::Gunner_State GunnerAttackRocket::getState()
{
	return eGunner_Attack_Rocket;
}
