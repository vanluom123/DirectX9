#include "BangerAttack.h"
#include "../BangerJump/BangerJump.h"

BangerAttack::BangerAttack(BangerData* banger) : BangerState(banger)
{
	_timeAttack = 0.0f;
	_count = -1;
}

void BangerAttack::Update(float dt)
{
	_pBangerData->banger->setVx(0);
	_timeAttack += dt;

	if (_timeAttack >= 0.45f)
	{
		_timeAttack = 0.0f;
		_count++;

		if (_count >= 3)
		{
			_pBangerData->banger->setState(new BangerJump(_pBangerData));
			return;
		}

		if (_pBangerData->banger->getListBullet()->size() < 4)
		{
			auto* ebullet = new BangerBullet();
			_pBangerData->banger->getListBullet()->push_back(ebullet);
		}

		float posX;
		float posY = _pBangerData->banger->getBound().top + 8;

		if (_pBangerData->banger->getReverse())
			posX = _pBangerData->banger->getBound().right - 8;
		else
			posX = _pBangerData->banger->getBound().left + 8;

		_pBangerData->banger->getListBullet()->at(_count)->setPosition(posX, posY);
		_pBangerData->banger->getListBullet()->at(_count)->setReverse(_pBangerData->banger->getReverse());
		_pBangerData->banger->getListBullet()->at(_count)->newObject();
	}
}

Banger::eBangerState BangerAttack::GetStateName()
{
	return Banger::eBangerState::BANGER_ATTACK;
}
