#include "BangerJump.h"
#include "../../../../../GameDefines/GameDefine.h"
#include "../BangerFall/BangerFall.h"

BangerJump::BangerJump(Banger* banger) :BangerState(banger)
{
	m_pBanger->setVy(Define::ENEMY_MIN_JUMP_VELOCITY);

	if (m_pBanger->getReverse())
		_bangerVx = 100.0f;
	else
		_bangerVx = -100.0f;

	_accelerateY = 15.0f;
}

BangerJump::~BangerJump()
{
}

void BangerJump::OnCollision(Side_Collision side)
{
	if (side == eSide_Top)
		m_pBanger->setState(new BangerFall(m_pBanger));
}

void BangerJump::Update(float dt)
{
	m_pBanger->setVx(_bangerVx);
	m_pBanger->addVy(_accelerateY);

	if (m_pBanger->getVy() > 0.0f)
		m_pBanger->setState(new BangerFall(m_pBanger));
}

Enumerator::Banger_State BangerJump::getState()
{
	return eBanger_Jump;
}
