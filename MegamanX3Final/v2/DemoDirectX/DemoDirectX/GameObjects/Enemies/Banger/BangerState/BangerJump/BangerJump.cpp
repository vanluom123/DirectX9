#include "BangerJump.h"
#include "../../../../../GameDefines/GameDefine.h"
#include "../BangerFall/BangerFall.h"

BangerJump::BangerJump(BangerData* banger) :BangerState(banger)
{
	_pBangerData->banger->SetVy(Define::ENEMY_MIN_JUMP_VELOCITY);

	if (_pBangerData->banger->GetReverse())
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
		_pBangerData->banger->SetState(new BangerFall(_pBangerData));
		break;
	default: break;
	}
}

void BangerJump::Update(float dt)
{	
	_pBangerData->banger->SetVx(_bangerVx);
	_pBangerData->banger->AddVy(_accelerateY);

	if (_pBangerData->banger->GetVy() > 0)
		_pBangerData->banger->SetState(new BangerFall(_pBangerData));
}

Banger::eBangerState BangerJump::GetStateName()
{
	return Banger::eBangerState::BANGER_JUMP;
}
