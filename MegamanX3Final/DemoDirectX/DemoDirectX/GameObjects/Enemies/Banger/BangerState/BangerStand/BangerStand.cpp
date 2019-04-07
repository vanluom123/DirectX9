#include "BangerStand.h"
#include "../../../../../GameDefines/GameDefine.h"
#include "../BangerAttack/BangerAttack.h"

BangerStand::BangerStand(BangerData* banger) : BangerState(banger)
{
	banger->GetBanger()->SetVx(0);
	banger->GetBanger()->SetVy(200);
	timePerShoot = 0.0f;
}

Banger::BangerStateName BangerStand::GetStateName()
{
	return Banger::BangerStateName::STAND;
}

void BangerStand::Update(float dt)
{
	banger->GetBanger()->SetVx(0);
	timePerShoot += dt;
	if (timePerShoot > 1.0f)
		banger->GetBanger()->SetState(new BangerAttack(banger));
}
