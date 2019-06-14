#include "BangerStand.h"
#include "../../../../../GameDefines/GameDefine.h"
#include "../BangerAttack/BangerAttack.h"

BangerStand::BangerStand(BangerData* banger) : BangerState(banger)
{
	_pBangerData->banger->setVx(0);
	_pBangerData->banger->setVy(200);
	_timePerShoot = 0.0f;
}

Banger::eBangerState BangerStand::GetStateName()
{
	return Banger::eBangerState::BANGER_STAND;
}

void BangerStand::Update(float dt)
{
	_pBangerData->banger->setVx(0);
	_timePerShoot += dt;
	if (_timePerShoot > 1.0f)
		_pBangerData->banger->setState(new BangerAttack(_pBangerData));
}
