#include "GunnerAttackRocket.h"
#include "GunnerAttack.h"

GunnerAttackRocket::GunnerAttackRocket(GunnerData* pGunner) :GunnerState(pGunner)
{
	pGunner->gunner->SetVy(200);
	pGunner->gunner->SetVx(0);
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
			_pGunnerData->gunner->SetState(new GunnerAttack(_pGunnerData));
			return;
		}

		if(_pGunnerData->gunner->GetListBullet()->empty())
		{
			auto* ebullet = new GunnerBullet();
			_pGunnerData->gunner->GetListBullet()->push_back(ebullet);
		}

		float posX = 0;
		float posY = _pGunnerData->gunner->GetBound().top + 12;

		if (_count == 0)
		{
			if (_pGunnerData->gunner->GetReverse())
				posX = _pGunnerData->gunner->GetBound().right - 10;
			else
				posX = _pGunnerData->gunner->GetBound().left + 10;
		}

		_pGunnerData->gunner->GetListBullet()->at(_count)->SetPosition(posX, posY);
		_pGunnerData->gunner->GetListBullet()->at(_count)->SetReverse(_pGunnerData->gunner->GetReverse());
		_pGunnerData->gunner->GetListBullet()->at(_count)->NewEntity();
	}
}