#ifndef GUNNER_STATE_H
#define GUNNER_STATE_H

#include "../Gunner.h"

class GunnerState
{
protected:
	Gunner* m_pGunner;
	int _count;
	float _timeAttack;
	float _accelerateY;

public:
	GunnerState(Gunner* headGunner);
	virtual ~GunnerState();
	virtual void OnCollision(Side_Collision side);
	virtual void Update(float dt);
	virtual Gunner_State getState();

};

#endif
