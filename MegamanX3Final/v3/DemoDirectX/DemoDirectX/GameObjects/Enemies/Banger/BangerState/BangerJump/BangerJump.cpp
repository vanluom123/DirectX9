#include "BangerJump.h"
#include "../../../../../GameDefines/GameDefine.h"
#include "../BangerFall/BangerFall.h"

BangerJump::BangerJump(BangerData* banger) :BangerState(banger)
{
	m_bangerData->banger->SetVy(Define::ENEMY_MIN_JUMP_VELOCITY);

	if (m_bangerData->banger->GetReverse())
		m_bangerVx = 100;
	else
		m_bangerVx = -100;

	m_accelerateY = 15.0f;
}

void BangerJump::OnCollision(BaseObject::eSideCollision side)
{
	switch (side)
	{
	case BaseObject::SIDE_COLLISION_LEFT:
	case BaseObject::SIDE_COLLISION_RIGHT:
		break;
	case BaseObject::SIDE_COLLISION_BOTTOM:
		break;
	case BaseObject::SIDE_COLLISION_TOP:
		m_bangerData->banger->SetState(new BangerFall(m_bangerData));
		break;
	default: break;
	}
}

void BangerJump::Update(float dt)
{	
	m_bangerData->banger->SetVx(m_bangerVx);
	m_bangerData->banger->AddVy(m_accelerateY);

	if (m_bangerData->banger->GetVy() > 0)
		m_bangerData->banger->SetState(new BangerFall(m_bangerData));
}

Banger::eBangerState BangerJump::GetStateName()
{
	return Banger::eBangerState::BANGER_JUMP;
}
