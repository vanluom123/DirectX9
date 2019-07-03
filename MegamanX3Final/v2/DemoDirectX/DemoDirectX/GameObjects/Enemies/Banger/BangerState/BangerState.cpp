#include "BangerState.h"


BangerState::BangerState(Banger* banger)
{
	m_pBanger = banger;
}

Banger_State BangerState::getState()
{
	return eBanger_None;
}

void BangerState::OnCollision(Side_Collision side)
{
}

void BangerState::Update(float dt)
{
}
