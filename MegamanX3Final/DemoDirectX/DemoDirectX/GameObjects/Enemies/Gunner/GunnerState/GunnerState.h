#ifndef GUNNER_STATE_H
#define GUNNER_STATE_H

#include "../Gunner.h"

class GunnerState
{
public:
	explicit GunnerState(GunnerData* headGunner);
	virtual ~GunnerState() = default;

	virtual Gunner::GunnerStateName getState() = 0;
	virtual void onCollision(Entity::SideCollisions side);
	virtual void update(float dt);

protected:
	GunnerData* pGunner;
	int count;
	float timeAttack;
	float translateY;
};
#endif
