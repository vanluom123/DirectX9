#ifndef _HEAD_GUNNER_STAND_STATE_H
#define _HEAD_GUNNER_STAND_STATE_H
#include "../GunnerState.h"

class GunnerStand :
	public GunnerState
{
public:
	GunnerStand(Gunner* headGunner);
	~GunnerStand();
	void Update(float dt) override;
	virtual Gunner_State getState() override;

};

#endif
