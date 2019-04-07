#ifndef _HEAD_GUNNER_STAND_STATE_H
#define _HEAD_GUNNER_STAND_STATE_H
#include "../GunnerState.h"

class GunnerStand :public GunnerState
{
public:
	explicit GunnerStand(GunnerData* headGunner);
	~GunnerStand() = default;

	Gunner::GunnerStateName getState() override;
	void update(float dt) override;
};

#endif
