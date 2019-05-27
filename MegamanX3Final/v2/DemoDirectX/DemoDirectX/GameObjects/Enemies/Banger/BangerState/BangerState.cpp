#include "BangerState.h"


BangerState::BangerState(BangerData* banger)
{
	this->_pBangerData = banger;
}

void BangerState::OnCollision(BaseObject::eSideCollision side)
{}

void BangerState::Update(float dt)
{}
