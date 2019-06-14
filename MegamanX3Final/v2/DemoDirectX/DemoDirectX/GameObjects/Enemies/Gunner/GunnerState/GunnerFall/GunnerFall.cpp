#include "GunnerFall.h"
#include "../../../../../GameDefines/GameDefine.h"
#include "../GunnerStand/GunnerStand.h"

GunnerFall::GunnerFall(GunnerData* headGunner) :GunnerState(headGunner)
{
	_pGunnerData->gunner->setVy(0);
	_accelerateY = 25.0f;
}

Gunner::eGunnerState GunnerFall::GetState()
{
	return Gunner::GUNNER_FALL;
}

void GunnerFall::OnCollision(BaseObject::eSideCollision side)
{
	if (side == BaseObject::BOTTOM)
		_pGunnerData->gunner->setState(new GunnerStand(_pGunnerData));
}

void GunnerFall::Update(float dt)
{
	_pGunnerData->gunner->addVy(_accelerateY);
	if (_pGunnerData->gunner->getVy() > Define::ENEMY_MAX_JUMP_VELOCITY)
		_pGunnerData->gunner->setVy(Define::ENEMY_MAX_JUMP_VELOCITY);
}
