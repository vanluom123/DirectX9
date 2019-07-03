#include "HelitDie.h"
#include "../../../../../GameDefines/GameDefine.h"
#include "../../../../../GameComponents/Sound.h"

HelitDie::HelitDie(Helit* helit) :HelitState(helit)
{
	Sound::getInstance()->play("explosions", false, 1);
	m_pHelit->setVy(Define::ENEMY_MIN_JUMP_VELOCITY);
    _timeDie = 0.0f;
    _accelerateY = 25.0f;
}

HelitDie::~HelitDie()
{
}

Helit_State HelitDie::getState()
{
	return eHelit_Death;
}

void HelitDie::update(float dt)
{
	m_pHelit->addVy(_accelerateY);

    _timeDie += dt;
    if (_timeDie >= 0.45f)
		m_pHelit->setDraw(false);
}
