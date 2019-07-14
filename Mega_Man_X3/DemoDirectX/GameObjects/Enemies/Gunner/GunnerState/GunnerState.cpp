#include "GunnerState.h"

GunnerState::GunnerState(Gunner* headGunner)
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
	return eGunner_None;
}
