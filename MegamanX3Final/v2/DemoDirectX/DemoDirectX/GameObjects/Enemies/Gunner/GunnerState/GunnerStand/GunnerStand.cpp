#include  "GunnerStand.h"
#include "../GunnerAttack/GunnerAttack.h"
#include "../GunnerAttack/GunnerAttackRocket.h"
#include "../../../Banger/BangerBullet/BangerBullet.h"

GunnerStand::GunnerStand(GunnerData* headGunner) :GunnerState(headGunner)
{
	_pGunnerData->gunner->setVx(0);
	_pGunnerData->gunner->setVy(200);
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
		_pGunnerData->gunner->setState(new GunnerAttackRocket(_pGunnerData));
}
