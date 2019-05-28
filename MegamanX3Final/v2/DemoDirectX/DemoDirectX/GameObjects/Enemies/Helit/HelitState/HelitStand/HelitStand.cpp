#include "HelitStand.h"
#include "../HelitAttack/HelitAttack.h"

HelitStand::HelitStand(HelitData* helit) :HelitState(helit)
{
	_pHelitData->helit->SetVx(0);
	_pHelitData->helit->SetVy(-60);
	_timeAttack = 0;
}

Helit::eHelitState HelitStand::GetState()
{
	return Helit::HELIT_STAND;
}

void HelitStand::Update(float dt)
{
	_timeAttack += dt;

	if (_timeAttack > 2.0f)
		_pHelitData->helit->SetState(new HelitAttack(_pHelitData));
	else
	{
		if (_timeAttack > 1.0f)
			_pHelitData->helit->SetVy(60);
	}

}
