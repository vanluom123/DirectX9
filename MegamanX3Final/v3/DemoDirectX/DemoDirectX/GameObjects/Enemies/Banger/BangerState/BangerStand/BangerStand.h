#ifndef BANGER_STAND_H
#define BANGER_STAND_H
#include "../BangerState.h"


class BangerStand :
	public BangerState
{
public:
	 BangerStand(BangerData* banger);

	Banger::eBangerState GetStateName() override;
	void Update(float dt) override;

private:
	float m_timePerShoot;

};

#endif // !BANGER_STAND_H
