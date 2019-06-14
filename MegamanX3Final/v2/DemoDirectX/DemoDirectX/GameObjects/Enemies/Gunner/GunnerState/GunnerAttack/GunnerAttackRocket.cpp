#include "GunnerAttackRocket.h"
#include "GunnerAttack.h"

GunnerAttackRocket::GunnerAttackRocket(GunnerData* pGunner) :GunnerState(pGunner)
{
	pGunner->gunner->setVy(200);
	pGunner->gunner->setVx(0);
	_timeAttack = 0;
	_count = -1;
}

Gunner::eGunnerState GunnerAttackRocket::GetState()
{
	return Gunner::GUNNER_ATTACK_ROCKET;
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
			_pGunnerData->gunner->setState(new GunnerAttack(_pGunnerData));
			return;
		}

		if(_pGunnerData->gunner->getListBullet()->empty())
		{
			auto ebullet = new GunnerBullet();
			_pGunnerData->gunner->getListBullet()->push_back(ebullet);
		}

		float posX = 0;
		float posY = _pGunnerData->gunner->getBound().top + 12;

		if (_count == 0)
		{
			if (_pGunnerData->gunner->getReverse())
				posX = _pGunnerData->gunner->getBound().right - 10;
			else
				posX = _pGunnerData->gunner->getBound().left + 10;
		}

		_pGunnerData->gunner->getListBullet()->at(_count)->setPosition(posX, posY);
		_pGunnerData->gunner->getListBullet()->at(_count)->setReverse(_pGunnerData->gunner->getReverse());
		_pGunnerData->gunner->getListBullet()->at(_count)->newObject();
	}
}