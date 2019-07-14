#include "GunnerDie.h"
#include "../../../../../GameDefines/GameDefine.h"
#include "../../../../../GameComponents/Sound.h"

GunnerDie::GunnerDie(Gunner* headGunner) :GunnerState(headGunner)
{
	Sound::getInstance()->play("explosions", false, 1);

	m_pGunner->setVy(Define::ENEMY_MIN_JUMP_VELOCITY);
	_timeDie = 0;
	_accelerateY = 25.0f;
}

GunnerDie::~GunnerDie()
{
}

void GunnerDie::Update(float dt)
{
	m_pGunner->addVy(_accelerateY);
	
	_timeDie += dt;
	if (_timeDie >= 0.45f)
	{
		m_pGunner->setDraw(false);
		return;
	}
}

Enumerator::Gunner_State GunnerDie::getState()
{
	return eGunner_Death;
}
