#include  "GunnerStand.h"
#include "../GunnerAttack/GunnerAttack.h"
#include "../GunnerAttack/GunnerAttackRocket.h"
#include "../../../Banger/BangerBullet/BangerBullet.h"

GunnerStand::GunnerStand(GunnerData* headGunner) :GunnerState(headGunner)
{
	_pGunnerData->gunner->SetVx(0);
	_pGunnerData->gunner->SetVy(200);
	_timeAttack = 0;
}

Gunner::eGunnerState GunnerStand::GetState()
{
	return Gunner::GUNNER_STAND;
}

void GunnerStand::Update(float dt)
{
	_timeAttack += dt;
	if (_timeAttack > 1.0f)
		_pGunnerData->gunner->SetState(new GunnerAttackRocket(_pGunnerData));
}
