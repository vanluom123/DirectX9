#include "GunnerState.h"

GunnerState::GunnerState(GunnerData* headGunner)
{
	this->m_gunnerData = headGunner;
}

void GunnerState::OnCollision(BaseObject::eSideCollision side)
{}

void GunnerState::Update(float dt)
{}
