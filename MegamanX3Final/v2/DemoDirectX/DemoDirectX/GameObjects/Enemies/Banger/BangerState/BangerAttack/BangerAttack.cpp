#include "BangerAttack.h"
#include "../BangerJump/BangerJump.h"

BangerAttack::BangerAttack(BangerData* banger) : BangerState(banger)
{
	_timeAttack = 0.0f;
	_count = -1;
}

void BangerAttack::Update(float dt)
{
	_pBangerData->banger->SetVx(0);
	_timeAttack += dt;

	if (_timeAttack >= 0.45f)
	{
		_timeAttack = 0.0f;
		_count++;

		if (_count >= 3)
		{
			_pBangerData->banger->SetState(new BangerJump(_pBangerData));
			return;
		}

		if (_pBangerData->banger->GetListBullet()->size() < 4)
		{
			auto* ebullet = new BangerBullet();
			_pBangerData->banger->GetListBullet()->push_back(ebullet);
		}

		float posX;
		float posY = _pBangerData->banger->GetBound().top + 8;

		if (_pBangerData->banger->GetReverse())
			posX = _pBangerData->banger->GetBound().right - 8;
		else
			posX = _pBangerData->banger->GetBound().left + 8;

		_pBangerData->banger->GetListBullet()->at(_count)->SetPosition(posX, posY);
		_pBangerData->banger->GetListBullet()->at(_count)->SetReverse(_pBangerData->banger->GetReverse());
		_pBangerData->banger->GetListBullet()->at(_count)->NewEntity();
	}
}

Banger::eBangerState BangerAttack::GetStateName()
{
	return Banger::eBangerState::BANGER_ATTACK;
}
