#include "GunnerAttack.h"
#include "../GunnerStand/GunnerStand.h"
#include "../../../Banger/BangerBullet/BangerBullet.h"
#include <iostream>
#include "GunnerAttackBullet.h"

GunnerAttack::GunnerAttack(GunnerData* headGunner) :GunnerState(headGunner)
{
	_pGunnerData->gunner->setVx(0);
	_pGunnerData->gunner->setVy(200);
	_timeAttack = 0;
	_count = 0;
}

Gunner::eGunnerState GunnerAttack::GetState()
{
	return Gunner::GUNNER_ATTACK;
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
			_pGunnerData->gunner->setState(new GunnerAttackBullet(_pGunnerData));
			return;
		}

		if (_pGunnerData->gunner->getListBullet()->size() < 3)
		{
			if (_count == 1)
			{
				auto* ebullet = new GunnerBullet();
				_pGunnerData->gunner->getListBullet()->push_back(ebullet);
			}
			
		}

		float posX = 0;
		float posY = _pGunnerData->gunner->getBound().top;

		if (_count == 1)
		{
			posY += 17;
			if (_pGunnerData->gunner->getReverse())
				posX = _pGunnerData->gunner->getBound().right;
			else
				posX = _pGunnerData->gunner->getBound().left;
		}

		_pGunnerData->gunner->getListBullet()->at(_count)->setPosition(posX, posY);
		_pGunnerData->gunner->getListBullet()->at(_count)->setReverse(_pGunnerData->gunner->getReverse());
		_pGunnerData->gunner->getListBullet()->at(_count)->newObject();
	}
}