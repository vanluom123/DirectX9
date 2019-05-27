#ifndef BANGER_FALL_H
#define BANGER_FALL_H
#include "../BangerState.h"

class BangerFall
	:public BangerState
{
private:
	float _bangerVx;

public:
	 BangerFall(BangerData* banger);

	void OnCollision(BaseObject::eSideCollision side) override;
	void Update(float dt) override;
	Banger::eBangerState GetStateName() override;
};

#endif // !BANGER_FALL_H
