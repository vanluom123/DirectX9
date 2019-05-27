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
	GunnerData* m_gunnerData;
	int m_count;
	float m_timeAttack;
	float m_accelerateY;
};
#endif
