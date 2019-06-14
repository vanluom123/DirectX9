#include "HelitStand.h"
#include "../HelitAttack/HelitAttack.h"

HelitStand::HelitStand(HelitData* helit) :HelitState(helit)
{
	_pHelitData->helit->setVx(0);
	_pHelitData->helit->setVy(-60);
	_timeAttack = 0;
}

Helit::eHelitState HelitStand::getState()
{
	return Helit::HELIT_STAND;
}

void HelitStand::update(float dt)
{
	_timeAttack += dt;

	if (_timeAttack > 2.0f)
		_pHelitData->helit->setState(new HelitAttack(_pHelitData));
	else
	{
		if (_timeAttack > 1.0f)
			_pHelitData->helit->setVy(60);
	}

}
