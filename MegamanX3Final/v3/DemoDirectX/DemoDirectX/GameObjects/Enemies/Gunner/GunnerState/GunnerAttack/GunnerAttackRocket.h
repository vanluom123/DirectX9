#ifndef GUNNER_ATTACK_TWICE_H
#define GUNNER_ATTACK_TWICE_H
#include "../GunnerState.h"

class GunnerAttackRocket :public GunnerState
{
public:
	GunnerAttackRocket(GunnerData* pGunner);

	Gunner::eGunnerState GetState() override;
	void Update(float dt) override;
};
#endif