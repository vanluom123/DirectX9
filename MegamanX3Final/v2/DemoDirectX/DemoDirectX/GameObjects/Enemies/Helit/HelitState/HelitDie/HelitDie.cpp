#include "HelitDie.h"
#include "../../../../../GameDefines/GameDefine.h"
#include "../../../../../GameComponents/Sound.h"

HelitDie::HelitDie(HelitData* helit) :HelitState(helit)
{
	Sound::GetInstance()->Play("explosions", false, 1);
	_pHelitData->helit->SetVy(Define::ENEMY_MIN_JUMP_VELOCITY);
    _timeDie = 0;
    _accelerateY = 25.0f;
}

Helit::eHelitState HelitDie::GetState()
{
    return Helit::HELIT_DIE;
}

void HelitDie::Update(float dt)
{
	_pHelitData->helit->AddVy(_accelerateY);

    _timeDie += dt;
    if (_timeDie >= 0.45f)
		_pHelitData->helit->SetDraw(false);
}
