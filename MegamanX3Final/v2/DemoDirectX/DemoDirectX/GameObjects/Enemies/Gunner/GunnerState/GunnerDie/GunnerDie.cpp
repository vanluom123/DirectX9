#include "GunnerDie.h"
#include "../../../../../GameDefines/GameDefine.h"
#include "../../../../../GameComponents/Sound.h"

GunnerDie::GunnerDie(GunnerData* headGunner) :GunnerState(headGunner)
{
	Sound::GetInstance()->Play("explosions", false, 1);

	_pGunnerData->gunner->SetVy(Define::ENEMY_MIN_JUMP_VELOCITY);
	_timeDie = 0;
	_accelerateY = 25.0f;
}

Gunner::eGunnerState GunnerDie::GetState()
{
	return Gunner::GUNNER_DIE;
}

void GunnerDie::Update(float dt)
{
	_pGunnerData->gunner->AddVy(_accelerateY);
	
	_timeDie += dt;
	if (_timeDie >= 0.45f)
	{
		_pGunnerData->gunner->SetDraw(false);
		return;
	}
}