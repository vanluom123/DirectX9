#include "GunnerState.h"

GunnerState::GunnerState(GunnerData* headGunner)
{
	this->pGunner = headGunner;
}

void GunnerState::onCollision(Entity::SideCollisions side)
{}

void GunnerState::update(float dt)
{}
