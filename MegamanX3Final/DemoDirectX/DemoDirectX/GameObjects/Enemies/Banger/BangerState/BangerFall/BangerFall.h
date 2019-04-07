#ifndef BANGER_FALL_H
#define BANGER_FALL_H
#include "../BangerState.h"

class BangerFall
	:public BangerState
{
protected:
	float Vx;
public:
	explicit BangerFall(BangerData* banger);
	~BangerFall() = default;

	void OnCollision(Entity::SideCollisions side) override;
	void Update(float dt) override;
	Banger::BangerStateName GetStateName() override;
};

#endif // !BANGER_FALL_H
