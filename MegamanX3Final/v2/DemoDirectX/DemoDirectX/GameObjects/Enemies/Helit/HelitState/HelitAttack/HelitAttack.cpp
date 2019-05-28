#include "HelitAttack.h"
#include "../HelitStand/HelitStand.h"

HelitAttack::HelitAttack(HelitData* helit) :HelitState(helit)
{
	_pHelitData->helit->SetVy(0);
	_pHelitData->helit->SetVx(0);
	_timeAttack = 0.0f;
	_count = -1;
}

Helit::eHelitState HelitAttack::GetState()
{
	return Helit::HELIT_ATTACK;
}

void HelitAttack::Update(float dt)
{
	_timeAttack += dt;
	if (_timeAttack >= 0.4f)
	{
		_timeAttack = 0;
		_count++;

		if (_count > 1)
		{
			_pHelitData->helit->SetState(new HelitStand(_pHelitData));
			return;
		}

		if (_pHelitData->helit->GetListBullet()->size() < 2)
		{
			auto* bullet = new HelitBullet();
			_pHelitData->helit->GetListBullet()->push_back(bullet);
		}

		float posX = 0;
		float posY = _pHelitData->helit->GetBound().top + 35;

		if (_pHelitData->helit->GetReverse())
			posX = _pHelitData->helit->GetBound().right - 10;
		else
			posX = _pHelitData->helit->GetBound().left + 10;


		_pHelitData->helit->GetListBullet()->at(_count)->SetPosition(posX, posY);
		_pHelitData->helit->GetListBullet()->at(_count)->SetReverse(_pHelitData->helit->GetReverse());
		_pHelitData->helit->GetListBullet()->at(_count)->NewEntity();
	}
}
