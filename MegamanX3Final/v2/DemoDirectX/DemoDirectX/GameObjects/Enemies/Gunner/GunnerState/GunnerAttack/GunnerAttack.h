#ifndef _ENEMIES_ATTACK_01_H
#define _ENEMIES_ATTACK_01_H
#include "../GunnerState.h"

class GunnerAttack :public GunnerState
{
public:
	GunnerAttack(GunnerData* headGunner);

	Gunner::eGunnerState GetState() override;
	void Update(float dt) override;
};
#endif
