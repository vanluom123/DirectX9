#include "BangerJump.h"
#include "../../../../../GameDefines/GameDefine.h"
#include "../BangerFall/BangerFall.h"

BangerJump::BangerJump(BangerData* banger) :BangerState(banger)
{
	banger->GetBanger()->SetVy(Define::ENEMY_MIN_JUMP_VELOCITY);

	if (banger->GetBanger()->GetReverse())
		Vx = 100;
	else
		Vx = -100;

	translateY = 15.0f;
}

void BangerJump::OnCollision(Entity::SideCollisions side)
{
	switch (side)
	{
	case Entity::LEFT:
	case Entity::RIGHT:
		break;
	case Entity::BOTTOM:
		break;
	case Entity::TOP:
		banger->GetBanger()->SetState(new BangerFall(banger));
		break;
	default: break;
	}
}

void BangerJump::Update(float dt)
{	
	banger->GetBanger()->SetVx(Vx);
	banger->GetBanger()->AddVy(translateY);
	if (banger->GetBanger()->GetVy() > 0)
		banger->GetBanger()->SetState(new BangerFall(banger));
}

Banger::BangerStateName BangerJump::GetStateName()
{
	return Banger::BangerStateName::JUMP;
}
