#ifndef _HEAD_GUNNER_STAND_STATE_H
#define _HEAD_GUNNER_STAND_STATE_H
#include "../GunnerState.h"

class GunnerStand :public GunnerState
{
public:
	GunnerStand(GunnerData* headGunner);

	Gunner::eGunnerState GetState() override;
	void Update(float dt) override;
};

#endif
