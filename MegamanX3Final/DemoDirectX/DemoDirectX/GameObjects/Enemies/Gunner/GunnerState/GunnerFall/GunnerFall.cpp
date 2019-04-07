#include "GunnerFall.h"
#include "../../../../../GameDefines/GameDefine.h"
#include "../GunnerStand/GunnerStand.h"

GunnerFall::GunnerFall(GunnerData* headGunner) :GunnerState(headGunner)
{
	pGunner->GetGunner()->SetVy(0);
	translateY = 25.0f;
}

Gunner::GunnerStateName GunnerFall::getState()
{
	return Gunner::FALL;
}

void GunnerFall::onCollision(Entity::SideCollisions side)
{
	if (side == Entity::BOTTOM)
		pGunner->GetGunner()->SetState(new GunnerStand(pGunner));
}

void GunnerFall::update(float dt)
{
	pGunner->GetGunner()->AddVy(translateY);
	if (pGunner->GetGunner()->GetVy() > Define::ENEMY_MAX_JUMP_VELOCITY)
		pGunner->GetGunner()->SetVy(Define::ENEMY_MAX_JUMP_VELOCITY);
}
