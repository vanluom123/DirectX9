#include "GunnerState.h"

GunnerState::GunnerState(Gunner* headGunner) :
	_count(0),
	_timeAttack(0),
	_accelerateY(0)
{
	m_pGunner = headGunner;
}

GunnerState::~GunnerState()
{
}

void GunnerState::OnCollision(Side_Collision side)
{
}

void GunnerState::Update(float dt)
{
}

Gunner_State GunnerState::getState()
{
	return Gunner_State::NONE;
}
