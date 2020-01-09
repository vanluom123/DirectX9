#include "GunnerAttackBullet.h"
#include "../GunnerStand/GunnerStand.h"
#include "../../../Banger/BangerBullet/BangerBullet.h"


GunnerAttackBullet::GunnerAttackBullet(Gunner* pGunner) :GunnerState(pGunner)
{
	_timeAttack = 0;
	_count = 1;
}

GunnerAttackBullet::~GunnerAttackBullet()
{
}

void GunnerAttackBullet::Update(float dt)
{
	_timeAttack += dt;
	if (_timeAttack > 1.0f)
	{
		_timeAttack = 0;
		_count++;

		if (_count > 4)
		{
			m_pGunner->setState(new GunnerStand(m_pGunner));
			return;
		}

		if (m_pGunner->getListBullet().size() < 5)
		{
			auto bullet = new BangerBullet();
			m_pGunner->insertBullet(bullet);
		}

		float posX = 0;
		float posY = m_pGunner->getBound().top;

		if (_count < 5)
		{
			if (m_pGunner->getReverse())
				posX = m_pGunner->getBound().right - 16;
			else
				posX = m_pGunner->getBound().left + 16;
		}

		m_pGunner->getIndexBullet(_count)->setPosition(posX, posY);
		m_pGunner->getIndexBullet(_count)->setReverse(m_pGunner->getReverse());
		m_pGunner->getIndexBullet(_count)->newObject();
	}
}

Enumerator::Gunner_State GunnerAttackBullet::getState()
{
	return Enumerator::Gunner_State::ATTACK_BULLET;
}
