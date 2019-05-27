#include "GunnerFall.h"
#include "../../../../../GameDefines/GameDefine.h"
#include "../GunnerStand/GunnerStand.h"

GunnerFall::GunnerFall(GunnerData* headGunner) :GunnerState(headGunner)
{
	_pGunnerData->gunner->SetVy(0);
	_accelerateY = 25.0f;
}

Gunner::eGunnerState GunnerFall::GetState()
{
	return Gunner::GUNNER_FALL;
}

void GunnerFall::OnCollision(BaseObject::eSideCollision side)
{
	if (side == BaseObject::BOTTOM)
		_pGunnerData->gunner->SetState(new GunnerStand(_pGunnerData));
}

void GunnerFall::Update(float dt)
{
	_pGunnerData->gunner->AddVy(_accelerateY);
	if (_pGunnerData->gunner->GetVy() > Define::ENEMY_MAX_JUMP_VELOCITY)
		_pGunnerData->gunner->SetVy(Define::ENEMY_MAX_JUMP_VELOCITY);
}
