#include "GunnerDie.h"
#include "../../../../../GameDefines/GameDefine.h"
#include "../../../../../GameComponents/Sound.h"

GunnerDie::GunnerDie(GunnerData* headGunner) :GunnerState(headGunner)
{
	Sound::GetInstance()->Play("explosions", false, 1);

	m_gunnerData->gunner->SetVy(Define::ENEMY_MIN_JUMP_VELOCITY);
	m_timeDie = 0;
	m_accelerateY = 25.0f;
}

Gunner::eGunnerState GunnerDie::GetState()
{
	return Gunner::GUNNER_DIE;
}

void GunnerDie::Update(float dt)
{
	m_gunnerData->gunner->AddVy(m_accelerateY);
	
	m_timeDie += dt;
	if (m_timeDie >= 0.45f)
	{
		m_gunnerData->gunner->SetDraw(false);
		return;
	}
}