#ifndef GUNNER_STATE_H
#define GUNNER_STATE_H

#include "../Gunner.h"

class GunnerState
{
public:
	GunnerState(GunnerData* headGunner);

	virtual Gunner::eGunnerState GetState() = 0;
	virtual void OnCollision(BaseObject::eSideCollision side);
	virtual void Update(float dt);

protected:
	GunnerData* _pGunnerData;
	int _count;
	float _timeAttack;
	float _accelerateY;
};
#endif
