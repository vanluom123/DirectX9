#include "BangerDie.h"

BangerDie::BangerDie(BangerData* banger) : BangerState(banger)
{
	Sound::getInstance()->play("explosions", false, 1);
	banger->GetBanger()->SetVy(Define::ENEMY_MIN_JUMP_VELOCITY);
	timeDie = 0;
	translateY = 25.0f;
}

Banger::BangerStateName BangerDie::GetStateName()
{
	return Banger::DIE;
}

void BangerDie::Update(float dt)
{
	banger->GetBanger()->SetVx(0);
	banger->GetBanger()->AddVy(translateY);

	timeDie += dt;
	if(timeDie >= 0.45f)
		banger->GetBanger()->SetDraw(false);
}
