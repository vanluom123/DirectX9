#include "GunnerFall.h"
#include "../../../../../GameDefines/GameDefine.h"
#include "../GunnerStand/GunnerStand.h"

GunnerFall::GunnerFall(GunnerData* headGunner) :GunnerState(headGunner)
{
	m_gunnerData->gunner->SetVy(0);
	m_accelerateY = 25.0f;
}

Gunner::eGunnerState GunnerFall::GetState()
{
	return Gunner::GUNNER_FALL;
}

void GunnerFall::OnCollision(BaseObject::eSideCollision side)
{
	if (side == BaseObject::SIDE_COLLISION_BOTTOM)
		m_gunnerData->gunner->SetState(new GunnerStand(m_gunnerData));
}

void GunnerFall::Update(float dt)
{
	m_gunnerData->gunner->AddVy(m_accelerateY);
	if (m_gunnerData->gunner->GetVy() > Define::ENEMY_MAX_JUMP_VELOCITY)
		m_gunnerData->gunner->SetVy(Define::ENEMY_MAX_JUMP_VELOCITY);
}
