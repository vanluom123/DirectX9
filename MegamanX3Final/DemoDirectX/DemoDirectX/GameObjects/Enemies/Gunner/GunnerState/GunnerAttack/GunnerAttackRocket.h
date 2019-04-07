#ifndef GUNNER_ATTACK_TWICE_H
#define GUNNER_ATTACK_TWICE_H
#include "../GunnerState.h"

class GunnerAttackRocket :public GunnerState
{
public:
	explicit GunnerAttackRocket(GunnerData* pGunner);
	~GunnerAttackRocket() = default;

	Gunner::GunnerStateName getState() override;
	void update(float dt) override;
};
#endif