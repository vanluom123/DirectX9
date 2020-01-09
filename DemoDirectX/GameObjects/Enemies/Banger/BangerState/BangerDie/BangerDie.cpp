#include "BangerDie.h"

BangerDie::BangerDie(Banger* banger) : BangerState(banger)
{
	Sound::getInstance()->play("explosions", false, 1);
	m_pBanger->setVy(Define::ENEMY_MIN_JUMP_VELOCITY);
	_timeDie = 0.0f;
	_accelerateY = 25.0f;
}

BangerDie::~BangerDie()
{
}

void BangerDie::Update(float dt)
{
	m_pBanger->setVx(0.0f);
	m_pBanger->addVy(_accelerateY);

	_timeDie += dt;
	if(_timeDie >= 0.45f)
		m_pBanger->setDraw(false);
}

Enumerator::Banger_State BangerDie::getState()
{
	return Enumerator::Banger_State::DEATH;
}
