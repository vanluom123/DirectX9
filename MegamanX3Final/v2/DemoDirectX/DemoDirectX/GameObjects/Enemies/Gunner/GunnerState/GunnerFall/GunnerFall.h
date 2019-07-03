#ifndef _HEAD_GUNNER_FALL_STATE_H
#define _HEAD_GUNNER_FALL_STATE_H
#include "../GunnerState.h"


class GunnerFall :public GunnerState
{
public:
	GunnerFall(Gunner* headGunner);
	~GunnerFall();
	void OnCollision(Side_Collision side) override;
	void Update(float dt) override;
	virtual Gunner_State getState() override;

};

#endif