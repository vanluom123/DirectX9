#ifndef BANGER_STATE_H
#define BANGER_STATE_H
#include "../Banger.h"

class BangerState
{

public:
	explicit BangerState(BangerData* banger);
	virtual ~BangerState() = default;

	virtual Banger::BangerStateName GetStateName() = 0;
	virtual void OnCollision(Entity::SideCollisions side);
	virtual void Update(float dt);

protected:
	BangerData* banger;
	float translateY;

};
#endif
