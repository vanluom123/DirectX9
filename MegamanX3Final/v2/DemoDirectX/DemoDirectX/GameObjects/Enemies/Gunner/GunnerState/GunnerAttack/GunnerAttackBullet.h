#ifndef GUNNER_ATTACK_BULLET_H
#define GUNNER_ATTACK_BULLET_H
#include "../GunnerState.h"

class GunnerAttackBullet :public GunnerState
{
public:
	GunnerAttackBullet(GunnerData* pGunner);

	Gunner::eGunnerState GetState() override;
	void Update(float dt) override;
};

#endif // !GUNNER_ATTACK_BULLET_H
