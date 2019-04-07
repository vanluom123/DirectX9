#include  "GunnerStand.h"
#include "../GunnerAttack/GunnerAttack.h"
#include "../GunnerAttack/GunnerAttackRocket.h"
#include "../../../Banger/BangerBullet/BangerBullet.h"

GunnerStand::GunnerStand(GunnerData* headGunner) :GunnerState(headGunner)
{
	pGunner->GetGunner()->SetVx(0);
	pGunner->GetGunner()->SetVy(200);
	timeAttack = 0;
}

Gunner::GunnerStateName GunnerStand::getState()
{
	return Gunner::STAND;
}

void GunnerStand::update(float dt)
{
	timeAttack += dt;
	if (timeAttack > 1.0f)
		pGunner->GetGunner()->SetState(new GunnerAttackRocket(pGunner));
}
