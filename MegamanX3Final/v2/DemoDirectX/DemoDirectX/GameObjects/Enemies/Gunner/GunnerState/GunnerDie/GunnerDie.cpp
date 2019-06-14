#include "GunnerDie.h"
#include "../../../../../GameDefines/GameDefine.h"
#include "../../../../../GameComponents/Sound.h"

GunnerDie::GunnerDie(GunnerData* headGunner) :GunnerState(headGunner)
{
	Sound::getInstance()->play("explosions", false, 1);

	_pGunnerData->gunner->setVy(Define::ENEMY_MIN_JUMP_VELOCITY);
	_timeDie = 0;
	_accelerateY = 25.0f;
}

Gunner::eGunnerState GunnerDie::GetState()
{
	return Gunner::GUNNER_DIE;
}

void GunnerDie::Update(float dt)
{
	_pGunnerData->gunner->addVy(_accelerateY);
	
	_timeDie += dt;
	if (_timeDie >= 0.45f)
	{
		_pGunnerData->gunner->setDraw(false);
		return;
	}
}