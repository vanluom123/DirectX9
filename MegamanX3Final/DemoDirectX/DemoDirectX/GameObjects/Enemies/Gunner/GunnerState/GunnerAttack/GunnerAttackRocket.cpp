#include "GunnerAttackRocket.h"
#include "GunnerAttack.h"

GunnerAttackRocket::GunnerAttackRocket(GunnerData* pGunner) :GunnerState(pGunner)
{
	pGunner->GetGunner()->SetVy(200);
	pGunner->GetGunner()->SetVx(0);
	timeAttack = 0;
	count = -1;
}

Gunner::GunnerStateName GunnerAttackRocket::getState()
{
	return Gunner::ATTACK_ROCKET;
}

void GunnerAttackRocket::update(float dt)
{
	timeAttack += dt;
	if (timeAttack >= 0.45f)
	{
		timeAttack = 0;
		count++;

		if (count > 0)
		{
			pGunner->GetGunner()->SetState(new GunnerAttack(pGunner));
			return;
		}

		if(pGunner->GetGunner()->GetListBullet()->empty())
		{
			auto* ebullet = new GunnerBullet();
			pGunner->GetGunner()->GetListBullet()->push_back(ebullet);
		}

		float posX = 0;
		float posY = pGunner->GetGunner()->GetBound().top + 12;

		if (count == 0)
		{
			if (pGunner->GetGunner()->GetReverse())
				posX = pGunner->GetGunner()->GetBound().right - 10;
			else
				posX = pGunner->GetGunner()->GetBound().left + 10;
		}

		pGunner->GetGunner()->GetListBullet()->at(count)->SetPosition(posX, posY);
		pGunner->GetGunner()->GetListBullet()->at(count)->SetReverse(pGunner->GetGunner()->GetReverse());
		pGunner->GetGunner()->GetListBullet()->at(count)->NewEntity();
	}
}