#include "GunnerDie.h"
#include "../../../../../GameDefines/GameDefine.h"
#include "../../../../../GameComponents/Sound.h"

GunnerDie::GunnerDie(GunnerData* headGunner) :GunnerState(headGunner)
{
	Sound::getInstance()->play("explosions", false, 1);

	pGunner->GetGunner()->SetVy(Define::ENEMY_MIN_JUMP_VELOCITY);
	timeDie = 0;
	translateY = 25.0f;
}

Gunner::GunnerStateName GunnerDie::getState()
{
	return Gunner::DIE;
}

void GunnerDie::update(float dt)
{
	pGunner->GetGunner()->AddVy(translateY);
	
	timeDie += dt;
	if (timeDie >= 0.45f)
	{
		pGunner->GetGunner()->SetDraw(false);
		return;
	}
}