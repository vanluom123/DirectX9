#ifndef BANGER_STATE_H
#define BANGER_STATE_H
#include "../Banger.h"

class BangerState
{

public:
	 BangerState(BangerData* banger);

	virtual Banger::eBangerState GetStateName() = 0;
	virtual void OnCollision(BaseObject::eSideCollision side);
	virtual void Update(float dt);

protected:
	BangerData* _pBangerData;
	float _accelerateY;

};
#endif
