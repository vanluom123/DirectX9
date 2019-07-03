#ifndef BANGER_STAND_H
#define BANGER_STAND_H
#include "../BangerState.h"


class BangerStand :
	public BangerState
{
public:
	 BangerStand(Banger* banger);
	 ~BangerStand();
	void Update(float dt) override;
	virtual Banger_State getState() override;

private:
	float _timePerShoot;

};

#endif // !BANGER_STAND_H
