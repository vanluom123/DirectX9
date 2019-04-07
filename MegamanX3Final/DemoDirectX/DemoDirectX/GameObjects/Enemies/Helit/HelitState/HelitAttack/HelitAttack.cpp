#include "HelitAttack.h"
#include "../HelitStand/HelitStand.h"

HelitAttack::HelitAttack(HelitData* helit) :HelitState(helit)
{
	helit->GetHelit()->SetVy(0);
	helit->GetHelit()->SetVx(0);
	timeAttack = 0.0f;
	count = -1;
}

Helit::StateName HelitAttack::getState()
{
	return Helit::Attack;
}

void HelitAttack::update(float dt)
{
	timeAttack += dt;
	if (timeAttack >= 0.4f)
	{
		timeAttack = 0;
		count++;

		if (count > 1)
		{
			helit->GetHelit()->setState(new HelitStand(helit));
			return;
		}

		if (helit->GetHelit()->GetListBullet()->size() < 2)
		{
			auto* bullet = new HelitBullet();
			helit->GetHelit()->GetListBullet()->push_back(bullet);
		}

		float posX = 0;
		float posY = helit->GetHelit()->GetBound().top + 35;

		if (helit->GetHelit()->GetReverse())
			posX = helit->GetHelit()->GetBound().right - 10;
		else
			posX = helit->GetHelit()->GetBound().left + 10;


		helit->GetHelit()->GetListBullet()->at(count)->SetPosition(posX, posY);
		helit->GetHelit()->GetListBullet()->at(count)->SetReverse(helit->GetHelit()->GetReverse());
		helit->GetHelit()->GetListBullet()->at(count)->NewEntity();
	}
}
