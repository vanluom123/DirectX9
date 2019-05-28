#ifndef _HEAD_GUNNER_DIE_H
#define _HEAD_GUNNER_DIE_H
#include "../GunnerState.h"

class GunnerDie : public GunnerState
{
public:
	GunnerDie(GunnerData* headGunner);

	Gunner::eGunnerState GetState() override;
	void Update(float dt) override;

private:
	float _timeDie;
};

#endif
