#ifndef BANGER_ATTACK_H
#define BANGER_ATTACK_H
#include "../BangerState.h"

class BangerAttack :
	public BangerState
{
public:
	explicit BangerAttack(BangerData* banger);
	~BangerAttack() = default;

	void Update(float dt) override;
	Banger::BangerStateName GetStateName() override;

protected:
	float timeAttack;
	int count;
};

#endif // !BANGER_ATTACK_H
