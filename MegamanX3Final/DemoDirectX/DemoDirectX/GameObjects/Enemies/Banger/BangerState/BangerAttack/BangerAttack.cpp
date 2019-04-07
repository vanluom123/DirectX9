#include "BangerAttack.h"
#include "../BangerJump/BangerJump.h"

BangerAttack::BangerAttack(BangerData* banger) : BangerState(banger)
{
	timeAttack = 0.0f;
	count = -1;
}

void BangerAttack::Update(float dt)
{
	banger->GetBanger()->SetVx(0);
	timeAttack += dt;

	if (timeAttack >= 0.45f)
	{
		timeAttack = 0.0f;
		count++;

		if (count >= 3)
		{
			banger->GetBanger()->SetState(new BangerJump(banger));
			return;
		}

		if (banger->GetBanger()->GetListBullet()->size() < 4)
		{
			auto* ebullet = new BangerBullet();
			banger->GetBanger()->GetListBullet()->push_back(ebullet);
		}

		float posX;
		float posY = banger->GetBanger()->GetBound().top + 8;

		if (banger->GetBanger()->GetReverse())
			posX = banger->GetBanger()->GetBound().right - 8;
		else
			posX = banger->GetBanger()->GetBound().left + 8;

		banger->GetBanger()->GetListBullet()->at(count)->SetPosition(posX, posY);
		banger->GetBanger()->GetListBullet()->at(count)->SetReverse(banger->GetBanger()->GetReverse());
		banger->GetBanger()->GetListBullet()->at(count)->NewEntity();
	}
}

Banger::BangerStateName BangerAttack::GetStateName()
{
	return Banger::BangerStateName::ATTACK;
}
