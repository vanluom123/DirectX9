#include "HelitDie.h"
#include "../../../../../GameDefines/GameDefine.h"
#include "../../../../../GameComponents/Sound.h"

HelitDie::HelitDie(HelitData* helit) :HelitState(helit)
{
	Sound::GetInstance()->Play("explosions", false, 1);
	m_helitData->helit->SetVy(Define::ENEMY_MIN_JUMP_VELOCITY);
    m_timeDie = 0;
    m_accelerateY = 25.0f;
}

Helit::eHelitState HelitDie::GetState()
{
    return Helit::HELIT_DIE;
}

void HelitDie::Update(float dt)
{
	m_helitData->helit->AddVy(m_accelerateY);

    m_timeDie += dt;
    if (m_timeDie >= 0.45f)
		m_helitData->helit->SetDraw(false);
}
