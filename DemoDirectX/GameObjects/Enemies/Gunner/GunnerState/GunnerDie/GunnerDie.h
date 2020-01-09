#ifndef _HEAD_GUNNER_DIE_H
#define _HEAD_GUNNER_DIE_H
#include "../GunnerState.h"

class GunnerDie : public GunnerState
{
private:
	float _timeDie;

public:
	GunnerDie(Gunner* headGunner);
	~GunnerDie();
	void Update(float dt) override;
	Gunner_State getState() override;
};

#endif
