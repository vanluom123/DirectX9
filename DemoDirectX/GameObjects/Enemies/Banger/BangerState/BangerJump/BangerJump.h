#ifndef BANGER_JUMP_H
#define BANGER_JUMP_H
#include "../BangerState.h"

class BangerJump :
	public BangerState
{
	float _bangerVx;

public:
	 BangerJump(Banger* banger);
	 ~BangerJump();
	void OnCollision(Side_Collision side) override;
	void Update(float dt) override;
	virtual Banger_State getState() override;

};
#endif
