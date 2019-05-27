#include "BangerState.h"


BangerState::BangerState(BangerData* banger)
{
	this->m_bangerData = banger;
}

void BangerState::OnCollision(BaseObject::eSideCollision side)
{}

void BangerState::Update(float dt)
{}
