#include "GunnerAttack.h"
#include "../GunnerStand/GunnerStand.h"
#include "../../../Banger/BangerBullet/BangerBullet.h"
#include <iostream>
#include "GunnerAttackBullet.h"

GunnerAttack::GunnerAttack(GunnerData* headGunner) :GunnerState(headGunner)
{
	_pGunnerData->gunner->SetVx(0);
	_pGunnerData->gunner->SetVy(200);
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
			_pGunnerData->gunner->SetState(new GunnerAttackBullet(_pGunnerData));
			return;
		}

		if (_pGunnerData->gunner->GetListBullet()->size() < 3)
		{
			if (_count == 1)
			{
				auto* ebullet = new GunnerBullet();
				_pGunnerData->gunner->GetListBullet()->push_back(ebullet);
			}
			
		}

		float posX = 0;
		float posY = _pGunnerData->gunner->GetBound().top;

		if (_count == 1)
		{
			posY += 17;
			if (_pGunnerData->gunner->GetReverse())
				posX = _pGunnerData->gunner->GetBound().right;
			else
				posX = _pGunnerData->gunner->GetBound().left;
		}

		_pGunnerData->gunner->GetListBullet()->at(_count)->SetPosition(posX, posY);
		_pGunnerData->gunner->GetListBullet()->at(_count)->SetReverse(_pGunnerData->gunner->GetReverse());
		_pGunnerData->gunner->GetListBullet()->at(_count)->NewEntity();
	}
}