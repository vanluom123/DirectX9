#include "GunnerAttack.h"
#include "../GunnerStand/GunnerStand.h"
#include "../../../Banger/BangerBullet/BangerBullet.h"
#include <iostream>
#include "GunnerAttackBullet.h"

GunnerAttack::GunnerAttack(Gunner* headGunner) :GunnerState(headGunner)
{
	m_pGunner->setVx(0);
	m_pGunner->setVy(200);
	_timeAttack = 0;
	_count = 0;
}

GunnerAttack::~GunnerAttack()
{
}

void GunnerAttack::Update(float dt)
{
	_timeAttack += dt;
	if (_timeAttack >= 0.45f)
	{
		_timeAttack = 0;
		_count++;

		if (_count > 1)
		{
			m_pGunner->setState(new GunnerAttackBullet(m_pGunner));
			return;
		}

		if(m_pGunner->getListBullet().size() < 3)
		{
			if(_count == 1)
			{
				auto bullet = new GunnerBullet();
				m_pGunner->insertBullet(bullet);
			}
		}
		
		float posX = 0;
		float posY = m_pGunner->getBound().top;

		if (_count == 1)
		{
			posY += 17;
			if (m_pGunner->getReverse())
				posX = m_pGunner->getBound().right;
			else
				posX = m_pGunner->getBound().left;
		}

		m_pGunner->getIndexBullet(_count)->setPosition(posX, posY);
		m_pGunner->getIndexBullet(_count)->setReverse(m_pGunner->getReverse());
		m_pGunner->getIndexBullet(_count)->newObject();
	}
}

Enumerator::Gunner_State GunnerAttack::getState()
{
	return Enumerator::Gunner_State::ATTACK;
}
