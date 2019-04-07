#include "BangerFall.h"
#include "../../../../../GameDefines/GameDefine.h"
#include "../BangerStand/BangerStand.h"

BangerFall::BangerFall(BangerData* banger) :BangerState(banger)
{
	translateY = 25.0f;

	if (banger->GetBanger()->GetVx() > 0)
		Vx = 100;
	else
		Vx = -100;

	banger->GetBanger()->SetVy(0);
}

void BangerFall::OnCollision(Entity::SideCollisions side)
{
	if (side == Entity::BOTTOM)
		banger->GetBanger()->SetState(new BangerStand(banger));
}

void BangerFall::Update(float dt)
{
	banger->GetBanger()->SetVx(Vx);
	banger->GetBanger()->AddVy(translateY);
	if (banger->GetBanger()->GetVy() > Define::ENEMY_MAX_JUMP_VELOCITY)
		banger->GetBanger()->SetVy(Define::ENEMY_MAX_JUMP_VELOCITY);
}

Banger::BangerStateName BangerFall::GetStateName()
{
	return Banger::BangerStateName::FALL;
}
