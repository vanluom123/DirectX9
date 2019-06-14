#include "BangerJump.h"
#include "../../../../../GameDefines/GameDefine.h"
#include "../BangerFall/BangerFall.h"

BangerJump::BangerJump(BangerData* banger) :BangerState(banger)
{
	_pBangerData->banger->setVy(Define::ENEMY_MIN_JUMP_VELOCITY);

	if (_pBangerData->banger->getReverse())
		_bangerVx = 100;
	else
		_bangerVx = -100;

	_accelerateY = 15.0f;
}

void BangerJump::OnCollision(BaseObject::eSideCollision side)
{
	switch (side)
	{
	case BaseObject::LEFT:
	case BaseObject::RIGHT:
		break;
	case BaseObject::BOTTOM:
		break;
	case BaseObject::TOP:
		_pBangerData->banger->setState(new BangerFall(_pBangerData));
		break;
	default: break;
	}
}

void BangerJump::Update(float dt)
{	
	_pBangerData->banger->setVx(_bangerVx);
	_pBangerData->banger->addVy(_accelerateY);

	if (_pBangerData->banger->getVy() > 0)
		_pBangerData->banger->setState(new BangerFall(_pBangerData));
}

Banger::eBangerState BangerJump::GetStateName()
{
	return Banger::eBangerState::BANGER_JUMP;
}
