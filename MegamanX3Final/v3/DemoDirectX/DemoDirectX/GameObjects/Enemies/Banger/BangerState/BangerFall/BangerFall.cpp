#include "BangerFall.h"
#include "../../../../../GameDefines/GameDefine.h"
#include "../BangerStand/BangerStand.h"

BangerFall::BangerFall(BangerData* banger) :BangerState(banger)
{
	m_accelerateY = 25.0f;

	if (m_bangerData->banger->GetVx() > 0)
		m_bangerVx = 100;
	else
		m_bangerVx = -100;

	m_bangerData->banger->SetVy(0);
}

void BangerFall::OnCollision(BaseObject::eSideCollision side)
{
	if (side == BaseObject::SIDE_COLLISION_BOTTOM)
		m_bangerData->banger->SetState(new BangerStand(m_bangerData));
}

void BangerFall::Update(float dt)
{
	m_bangerData->banger->SetVx(m_bangerVx);
	m_bangerData->banger->AddVy(m_accelerateY);
	if (m_bangerData->banger->GetVy() > Define::ENEMY_MAX_JUMP_VELOCITY)
		m_bangerData->banger->SetVy(Define::ENEMY_MAX_JUMP_VELOCITY);
}

Banger::eBangerState BangerFall::GetStateName()
{
	return Banger::eBangerState::BANGER_FALL;
}
