#ifndef _HEAD_GUNNER_DIE_H
#define _HEAD_GUNNER_DIE_H
#include "../GunnerState.h"

class GunnerDie : public GunnerState
{
public:
	GunnerDie(Gunner* headGunner);
	~GunnerDie();
	void Update(float dt) override;
	virtual Gunner_State getState() override;

private:
	float _timeDie;
};

#endif
