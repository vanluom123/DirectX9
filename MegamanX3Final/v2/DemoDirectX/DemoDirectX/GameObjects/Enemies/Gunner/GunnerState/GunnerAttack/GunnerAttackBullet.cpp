#include "GunnerAttackBullet.h"
#include "../GunnerStand/GunnerStand.h"
#include "../../../Banger/BangerBullet/BangerBullet.h"


GunnerAttackBullet::GunnerAttackBullet(GunnerData* pGunner) :GunnerState(pGunner)
{
	_timeAttack = 0;
	_count = 1;
}

Gunner::eGunnerState GunnerAttackBullet::GetState()
{
	return Gunner::GUNNER_ATTACK_BULLET;
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
			_pGunnerData->gunner->setState(new GunnerStand(_pGunnerData));
			return;
		}

		if (_pGunnerData->gunner->getListBullet()->size() < 5)
		{
			auto* ebullet = new BangerBullet();
			_pGunnerData->gunner->getListBullet()->push_back(ebullet);
		}

		float posX = 0;
		float posY = _pGunnerData->gunner->getBound().top;

		if (_count < 5)
		{
			if (_pGunnerData->gunner->getReverse())
				posX = _pGunnerData->gunner->getBound().right - 16;
			else
				posX = _pGunnerData->gunner->getBound().left + 16;
		}

		_pGunnerData->gunner->getListBullet()->at(_count)->setPosition(posX, posY);
		_pGunnerData->gunner->getListBullet()->at(_count)->setReverse(_pGunnerData->gunner->getReverse());
		_pGunnerData->gunner->getListBullet()->at(_count)->newObject();
	}
}