#ifndef _ENEMIES_ATTACK_01_H
#define _ENEMIES_ATTACK_01_H
#include "../GunnerState.h"

class GunnerAttack :public GunnerState
{
public:
	explicit GunnerAttack(GunnerData* headGunner);
	~GunnerAttack() = default;

	Gunner::GunnerStateName getState() override;
	void update(float dt) override;
};
#endif
