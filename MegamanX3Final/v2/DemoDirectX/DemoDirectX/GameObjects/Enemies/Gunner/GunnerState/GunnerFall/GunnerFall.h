#ifndef _HEAD_GUNNER_FALL_STATE_H
#define _HEAD_GUNNER_FALL_STATE_H
#include "../GunnerState.h"


class GunnerFall :public GunnerState
{
public:
	GunnerFall(GunnerData* headGunner);

	Gunner::eGunnerState GetState() override;
	void OnCollision(BaseObject::eSideCollision side) override;
	void Update(float dt) override;
};

#endif