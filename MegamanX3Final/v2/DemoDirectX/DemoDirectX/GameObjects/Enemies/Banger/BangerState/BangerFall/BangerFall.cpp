#include "BangerFall.h"
#include "../../../../../GameDefines/GameDefine.h"
#include "../BangerStand/BangerStand.h"

BangerFall::BangerFall(BangerData* banger) :BangerState(banger)
{
	_accelerateY = 25.0f;

	if (_pBangerData->banger->getVx() > 0)
		_bangerVx = 100;
	else
		_bangerVx = -100;

	_pBangerData->banger->setVy(0);
}

void BangerFall::OnCollision(BaseObject::eSideCollision side)
{
	if (side == BaseObject::BOTTOM)
		_pBangerData->banger->setState(new BangerStand(_pBangerData));
}

void BangerFall::Update(float dt)
{
	_pBangerData->banger->setVx(_bangerVx);
	_pBangerData->banger->addVy(_accelerateY);
	if (_pBangerData->banger->getVy() > Define::ENEMY_MAX_JUMP_VELOCITY)
		_pBangerData->banger->setVy(Define::ENEMY_MAX_JUMP_VELOCITY);
}

Banger::eBangerState BangerFall::GetStateName()
{
	return Banger::eBangerState::BANGER_FALL;
}
