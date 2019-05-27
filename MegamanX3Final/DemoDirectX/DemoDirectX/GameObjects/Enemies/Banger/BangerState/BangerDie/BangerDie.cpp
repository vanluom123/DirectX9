#include "BangerDie.h"

BangerDie::BangerDie(BangerData* banger) : BangerState(banger)
{
	Sound::getInstance()->play("explosions", false, 1);
	_pBangerData->banger->SetVy(Define::ENEMY_MIN_JUMP_VELOCITY);
	_timeDie = 0;
	_accelerateY = 25.0f;
}

Banger::eBangerState BangerDie::GetStateName()
{
	return Banger::BANGER_DIE;
}

void BangerDie::Update(float dt)
{
	_pBangerData->banger->SetVx(0);
	_pBangerData->banger->AddVy(_accelerateY);

	_timeDie += dt;
	if(_timeDie >= 0.45f)
		_pBangerData->banger->SetDraw(false);
}
