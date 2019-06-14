#include "HelitDie.h"
#include "../../../../../GameDefines/GameDefine.h"
#include "../../../../../GameComponents/Sound.h"

HelitDie::HelitDie(HelitData* helit) :HelitState(helit)
{
	Sound::getInstance()->play("explosions", false, 1);
	_pHelitData->helit->setVy(Define::ENEMY_MIN_JUMP_VELOCITY);
    _timeDie = 0;
    _accelerateY = 25.0f;
}

Helit::eHelitState HelitDie::getState()
{
    return Helit::HELIT_DIE;
}

void HelitDie::update(float dt)
{
	_pHelitData->helit->addVy(_accelerateY);

    _timeDie += dt;
    if (_timeDie >= 0.45f)
		_pHelitData->helit->setDraw(false);
}
