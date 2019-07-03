#ifndef GUNNER_ATTACK_BULLET_H
#define GUNNER_ATTACK_BULLET_H
#include "../GunnerState.h"

class GunnerAttackBullet :public GunnerState
{
public:
	GunnerAttackBullet(Gunner* pGunner);
	~GunnerAttackBullet();
	void Update(float dt) override;
	virtual Gunner_State getState() override;

};

#endif // !GUNNER_ATTACK_BULLET_H
