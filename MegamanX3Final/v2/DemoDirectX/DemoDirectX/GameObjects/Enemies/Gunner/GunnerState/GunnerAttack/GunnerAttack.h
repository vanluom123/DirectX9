#ifndef _ENEMIES_ATTACK_01_H
#define _ENEMIES_ATTACK_01_H
#include "../GunnerState.h"

class GunnerAttack :public GunnerState
{
public:
	GunnerAttack(Gunner* headGunner);
	~GunnerAttack();
	void Update(float dt) override;

	virtual Gunner_State getState() override;

};
#endif
