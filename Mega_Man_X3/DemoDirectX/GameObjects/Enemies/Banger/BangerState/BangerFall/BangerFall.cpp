#include "BangerFall.h"
#include "../../../../../GameDefines/GameDefine.h"
#include "../BangerStand/BangerStand.h"

BangerFall::BangerFall(Banger* banger) :BangerState(banger)
{
	_accelerateY = 25.0f;

	if (m_pBanger->getVx() > 0.0f)
		_bangerVx = 100.0f;
	else
		_bangerVx = -100.0f;

	m_pBanger->setVy(0.0f);
}

BangerFall::~BangerFall()
{
}

void BangerFall::OnCollision(Side_Collision side)
{
	if (side == eSide_Bottom)
		m_pBanger->setState(new BangerStand(m_pBanger));
}

void BangerFall::Update(float dt)
{
	m_pBanger->setVx(_bangerVx);
	m_pBanger->addVy(_accelerateY);
	if (m_pBanger->getVy() > Define::ENEMY_MAX_JUMP_VELOCITY)
		m_pBanger->setVy(Define::ENEMY_MAX_JUMP_VELOCITY);
}

Enumerator::Banger_State BangerFall::getState()
{
	return eBanger_Fall;
}
