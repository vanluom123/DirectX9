#ifndef BANGER_STATE_H
#define BANGER_STATE_H
#include "../Banger.h"

class BangerState
{
public:
	BangerState(Banger* banger);
	virtual ~BangerState() = default;

	virtual Banger_State getState();
	virtual void OnCollision(Side_Collision side);
	virtual void Update(float dt);

protected:
	float _accelerateY;
	Banger* m_pBanger;
};
#endif
