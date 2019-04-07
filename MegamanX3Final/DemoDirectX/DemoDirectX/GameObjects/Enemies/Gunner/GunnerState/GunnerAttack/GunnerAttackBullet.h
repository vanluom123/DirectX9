#ifndef GUNNER_ATTACK_BULLET_H
#define GUNNER_ATTACK_BULLET_H
#include "../GunnerState.h"

class GunnerAttackBullet :
	public GunnerState
{
public:
	explicit GunnerAttackBullet(GunnerData* pGunner);
	~GunnerAttackBullet() = default;

	Gunner::GunnerStateName getState() override;
	void update(float dt) override;
};
#endif // !GUNNER_ATTACK_BULLET_H
