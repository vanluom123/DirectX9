#include "GunnerState.h"

GunnerState::GunnerState(GunnerData* headGunner)
{
	this->_pGunnerData = headGunner;
}

void GunnerState::OnCollision(BaseObject::eSideCollision side)
{}

void GunnerState::Update(float dt)
{}
