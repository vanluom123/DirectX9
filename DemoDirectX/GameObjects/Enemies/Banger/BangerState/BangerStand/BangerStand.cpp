#include "BangerStand.h"
#include "../BangerAttack/BangerAttack.h"

BangerStand::BangerStand(Banger* banger) : BangerState(banger)
{
	m_pBanger->setVx(0.0f);
	m_pBanger->setVy(200.0f);
	_timePerShoot = 0.0f;
}

BangerStand::~BangerStand()
{
}


void BangerStand::Update(float dt)
{
	m_pBanger->setVx(0.0f);
	_timePerShoot += dt;
	if (_timePerShoot > 1.0f)
		m_pBanger->setState(new BangerAttack(m_pBanger));
}

Enumerator::Banger_State BangerStand::getState()
{
	return Enumerator::Banger_State::STAND;
}
