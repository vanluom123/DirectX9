#ifndef BANGER_JUMP_H
#define BANGER_JUMP_H
#include "../BangerState.h"

class BangerJump :
	public BangerState
{
private:
	float m_bangerVx;

public:
	 BangerJump(BangerData* banger);

	void OnCollision(BaseObject::eSideCollision side) override;
	void Update(float dt) override;
	Banger::eBangerState GetStateName() override;
};
#endif
