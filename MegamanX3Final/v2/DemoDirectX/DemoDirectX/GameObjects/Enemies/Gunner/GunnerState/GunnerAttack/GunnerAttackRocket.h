#ifndef GUNNER_ATTACK_TWICE_H
#define GUNNER_ATTACK_TWICE_H
#include "../GunnerState.h"

class GunnerAttackRocket :public GunnerState
{
public:
	GunnerAttackRocket(Gunner* pGunner);
	~GunnerAttackRocket();
	void Update(float dt) override;
	virtual Gunner_State getState() override;

};
#endif