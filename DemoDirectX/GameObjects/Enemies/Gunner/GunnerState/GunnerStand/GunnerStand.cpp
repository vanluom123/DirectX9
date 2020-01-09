#include  "GunnerStand.h"
#include "../GunnerAttack/GunnerAttack.h"
#include "../GunnerAttack/GunnerAttackRocket.h"
#include "../../../Banger/BangerBullet/BangerBullet.h"

GunnerStand::GunnerStand(Gunner* headGunner) : GunnerState(headGunner)
{
	m_pGunner->setVx(0);
	m_pGunner->setVy(200);
	_timeAttack = 0;
}

GunnerStand::~GunnerStand()
{
}

void GunnerStand::Update(float dt)
{
	_timeAttack += dt;
	if (_timeAttack > 1.0f)
		m_pGunner->setState(new GunnerAttackRocket(m_pGunner));
}

Gunner_State GunnerStand::getState()
{
	return Gunner_State::STAND;
}
