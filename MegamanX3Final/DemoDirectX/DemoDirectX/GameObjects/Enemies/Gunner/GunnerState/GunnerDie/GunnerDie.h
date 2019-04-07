#ifndef _HEAD_GUNNER_DIE_H
#define _HEAD_GUNNER_DIE_H
#include "../GunnerState.h"

class GunnerDie : public GunnerState
{
public:
	explicit GunnerDie(GunnerData* headGunner);
	~GunnerDie() = default;

	Gunner::GunnerStateName getState() override;
	void update(float dt) override;

private:
	float timeDie;
};

#endif
