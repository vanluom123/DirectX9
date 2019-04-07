#include "HelitStand.h"
#include "../HelitAttack/HelitAttack.h"

HelitStand::HelitStand(HelitData* helit) :HelitState(helit)
{
	helit->GetHelit()->SetVx(0);
	helit->GetHelit()->SetVy(-60);
	timeAttack = 0;
}

Helit::StateName HelitStand::getState()
{
	return Helit::Stand;
}

void HelitStand::update(float dt)
{
	timeAttack += dt;

	if (timeAttack > 2.0f)
		helit->GetHelit()->setState(new HelitAttack(helit));
	else
	{
		if (timeAttack > 1.0f)
			helit->GetHelit()->SetVy(60);
	}

}
