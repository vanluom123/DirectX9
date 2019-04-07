#include "GunnerAttack.h"
#include "../GunnerStand/GunnerStand.h"
#include "../../../Banger/BangerBullet/BangerBullet.h"
#include <iostream>
#include "GunnerAttackBullet.h"

GunnerAttack::GunnerAttack(GunnerData* headGunner) :GunnerState(headGunner)
{
	pGunner->GetGunner()->SetVx(0);
	pGunner->GetGunner()->SetVy(200);
	timeAttack = 0;
	count = 0;
}

Gunner::GunnerStateName GunnerAttack::getState()
{
	return Gunner::ATTACK;
}

void GunnerAttack::update(float dt)
{
	timeAttack += dt;
	if (timeAttack >= 0.45f)
	{
		timeAttack = 0;
		count++;

		if (count > 1)
		{
			pGunner->GetGunner()->SetState(new GunnerAttackBullet(pGunner));
			return;
		}

		if (pGunner->GetGunner()->GetListBullet()->size() < 3)
		{
			if (count == 1)
			{
				auto* ebullet = new GunnerBullet();
				pGunner->GetGunner()->GetListBullet()->push_back(ebullet);
			}
			
		}

		float posX = 0;
		float posY = pGunner->GetGunner()->GetBound().top;

		if (count == 1)
		{
			posY += 17;
			if (pGunner->GetGunner()->GetReverse())
				posX = pGunner->GetGunner()->GetBound().right;
			else
				posX = pGunner->GetGunner()->GetBound().left;
		}

		pGunner->GetGunner()->GetListBullet()->at(count)->SetPosition(posX, posY);
		pGunner->GetGunner()->GetListBullet()->at(count)->SetReverse(pGunner->GetGunner()->GetReverse());
		pGunner->GetGunner()->GetListBullet()->at(count)->NewEntity();
	}
}