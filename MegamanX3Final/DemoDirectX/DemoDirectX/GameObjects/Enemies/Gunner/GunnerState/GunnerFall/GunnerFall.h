#ifndef _HEAD_GUNNER_FALL_STATE_H
#define _HEAD_GUNNER_FALL_STATE_H
#include "../GunnerState.h"


class GunnerFall :public GunnerState
{
public:
	explicit GunnerFall(GunnerData* headGunner);
	~GunnerFall() = default;

	Gunner::GunnerStateName getState() override;
	void onCollision(Entity::SideCollisions side) override;
	void update(float dt) override;
};

#endif