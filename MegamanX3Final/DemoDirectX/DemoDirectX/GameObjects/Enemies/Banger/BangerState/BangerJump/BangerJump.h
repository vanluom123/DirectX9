#ifndef BANGER_JUMP_H
#define BANGER_JUMP_H
#include "../BangerState.h"

class BangerJump :
	public BangerState
{
protected:
	float Vx;
public:
	explicit BangerJump(BangerData* banger);
	~BangerJump() = default;

	void OnCollision(Entity::SideCollisions side) override;
	void Update(float dt) override;
	Banger::BangerStateName GetStateName() override;
};
#endif
