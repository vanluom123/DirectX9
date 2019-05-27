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
			_pGunnerData->gunner->SetState(new GunnerStand(_pGunnerData));
			return;
		}

		if (_pGunnerData->gunner->GetListBullet()->size() < 5)
		{
			auto* ebullet = new BangerBullet();
			_pGunnerData->gunner->GetListBullet()->push_back(ebullet);
		}

		float posX = 0;
		float posY = _pGunnerData->gunner->GetBound().top;

		if (_count < 5)
		{
			if (_pGunnerData->gunner->GetReverse())
				posX = _pGunnerData->gunner->GetBound().right - 16;
			else
				posX = _pGunnerData->gunner->GetBound().left + 16;
		}

		_pGunnerData->gunner->GetListBullet()->at(_count)->SetPosition(posX, posY);
		_pGunnerData->gunner->GetListBullet()->at(_count)->SetReverse(_pGunnerData->gunner->GetReverse());
		_pGunnerData->gunner->GetListBullet()->at(_count)->NewEntity();
	}
}