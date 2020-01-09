#include "GunnerFall.h"
#include "../../../../../GameDefines/GameDefine.h"
#include "../GunnerStand/GunnerStand.h"

GunnerFall::GunnerFall(Gunner* headGunner) :GunnerState(headGunner)
{
	m_pGunner->setVy(0);
	_accelerateY = 25.0f;
}

GunnerFall::~GunnerFall()
{
}

void GunnerFall::OnCollision(Side_Collision side)
{
	if (side == Enumerator::Side_Collision::BOTTOM)
		m_pGunner->setState(new GunnerStand(m_pGunner));
}

void GunnerFall::Update(float dt)
{
	m_pGunner->addVy(_accelerateY);
	if (m_pGunner->getVy() > Define::ENEMY_MAX_JUMP_VELOCITY)
		m_pGunner->setVy(Define::ENEMY_MAX_JUMP_VELOCITY);
}

Enumerator::Gunner_State GunnerFall::getState()
{
	return Enumerator::Gunner_State::FALL;
}
