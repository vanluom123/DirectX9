#include "HelitDie.h"
#include "../../../../../GameDefines/GameDefine.h"
#include "../../../../../GameComponents/Sound.h"

HelitDie::HelitDie(HelitData* helit) :HelitState(helit)
{
	Sound::getInstance()->play("explosions", false, 1);
	helit->GetHelit()->SetVy(Define::ENEMY_MIN_JUMP_VELOCITY);
    timeDie = 0;
    translateY = 25.0f;
}

Helit::StateName HelitDie::getState()
{
    return Helit::Die;
}

void HelitDie::update(float dt)
{
	helit->GetHelit()->AddVy(translateY);

    timeDie += dt;
    if (timeDie >= 0.45f)
		helit->GetHelit()->SetDraw(false);
}
