#include "HelitAttack.h"
#include "../HelitStand/HelitStand.h"

HelitAttack::HelitAttack(HelitData* helit) :HelitState(helit)
{
	_pHelitData->helit->setVy(0);
	_pHelitData->helit->setVx(0);
	_timeAttack = 0.0f;
	_count = -1;
}

Helit::eHelitState HelitAttack::getState()
{
	return Helit::HELIT_ATTACK;
}

void HelitAttack::update(float dt)
{
	_timeAttack += dt;
	if (_timeAttack >= 0.4f)
	{
		_timeAttack = 0;
		_count++;

		if (_count > 1)
		{
			_pHelitData->helit->setState(new HelitStand(_pHelitData));
			return;
		}

		if (_pHelitData->helit->getListBullet()->size() < 2)
		{
			auto* bullet = new HelitBullet();
			_pHelitData->helit->getListBullet()->push_back(bullet);
		}

		float posX = 0;
		float posY = _pHelitData->helit->getBound().top + 35;

		if (_pHelitData->helit->getReverse())
			posX = _pHelitData->helit->getBound().right - 10;
		else
			posX = _pHelitData->helit->getBound().left + 10;


		_pHelitData->helit->getListBullet()->at(_count)->setPosition(posX, posY);
		_pHelitData->helit->getListBullet()->at(_count)->setReverse(_pHelitData->helit->getReverse());
		_pHelitData->helit->getListBullet()->at(_count)->newObject();
	}
}
