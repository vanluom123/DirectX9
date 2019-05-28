#include "BangerFall.h"
#include "../../../../../GameDefines/GameDefine.h"
#include "../BangerStand/BangerStand.h"

BangerFall::BangerFall(BangerData* banger) :BangerState(banger)
{
	_accelerateY = 25.0f;

	if (_pBangerData->banger->GetVx() > 0)
		_bangerVx = 100;
	else
		_bangerVx = -100;

	_pBangerData->banger->SetVy(0);
}

void BangerFall::OnCollision(BaseObject::eSideCollision side)
{
	if (side == BaseObject::BOTTOM)
		_pBangerData->banger->SetState(new BangerStand(_pBangerData));
}

void BangerFall::Update(float dt)
{
	_pBangerData->banger->SetVx(_bangerVx);
	_pBangerData->banger->AddVy(_accelerateY);
	if (_pBangerData->banger->GetVy() > Define::ENEMY_MAX_JUMP_VELOCITY)
		_pBangerData->banger->SetVy(Define::ENEMY_MAX_JUMP_VELOCITY);
}

Banger::eBangerState BangerFall::GetStateName()
{
	return Banger::eBangerState::BANGER_FALL;
}
