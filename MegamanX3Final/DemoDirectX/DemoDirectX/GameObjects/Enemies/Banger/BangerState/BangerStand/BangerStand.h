#ifndef BANGER_STAND_H
#define BANGER_STAND_H
#include "../BangerState.h"


class BangerStand :
	public BangerState
{
public:
	explicit BangerStand(BangerData* banger);
	~BangerStand() = default;

	Banger::BangerStateName GetStateName() override;
	void Update(float dt) override;

protected:
	float timePerShoot;

};

#endif // !BANGER_STAND_H
