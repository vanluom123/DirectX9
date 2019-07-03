#ifndef BANGER_FALL_H
#define BANGER_FALL_H
#include "../BangerState.h"

class BangerFall
	:public BangerState
{
private:
	float _bangerVx;

public:
	 BangerFall(Banger* banger);
	 ~BangerFall();
	void OnCollision(Side_Collision side) override;
	void Update(float dt) override;
	virtual Banger_State getState() override;

};

#endif // !BANGER_FALL_H
