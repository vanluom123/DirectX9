#include "GunnerAttackBullet.h"
#include "../GunnerStand/GunnerStand.h"
#include "../../../Banger/BangerBullet/BangerBullet.h"


GunnerAttackBullet::GunnerAttackBullet(GunnerData* pGunner) :GunnerState(pGunner)
{
	timeAttack = 0;
	count = 1;
}

Gunner::GunnerStateName GunnerAttackBullet::getState()
{
	return Gunner::ATTACK_BULLET;
}

void GunnerAttackBullet::update(float dt)
{
	timeAttack += dt;
	if (timeAttack > 1.0f)
	{
		timeAttack = 0;
		count++;

		if (count > 4)
		{
			pGunner->GetGunner()->SetState(new GunnerStand(pGunner));
			return;
		}

		if (pGunner->GetGunner()->GetListBullet()->size() < 5)
		{
			auto* ebullet = new BangerBullet();
			pGunner->GetGunner()->GetListBullet()->push_back(ebullet);
		}

		float posX = 0;
		float posY = pGunner->GetGunner()->GetBound().top;

		if (count < 5)
		{
			if (pGunner->GetGunner()->GetReverse())
				posX = pGunner->GetGunner()->GetBound().right - 16;
			else
				posX = pGunner->GetGunner()->GetBound().left + 16;
		}

		pGunner->GetGunner()->GetListBullet()->at(count)->SetPosition(posX, posY);
		pGunner->GetGunner()->GetListBullet()->at(count)->SetReverse(pGunner->GetGunner()->GetReverse());
		pGunner->GetGunner()->GetListBullet()->at(count)->NewEntity();
	}
}