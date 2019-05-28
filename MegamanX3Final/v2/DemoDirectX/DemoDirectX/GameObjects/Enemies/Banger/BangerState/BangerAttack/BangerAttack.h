#ifndef BANGER_ATTACK_H
#define BANGER_ATTACK_H
#include "../BangerState.h"

class BangerAttack :
	public BangerState
{
public:
	 BangerAttack(BangerData* banger);

	void Update(float dt) override;
	Banger::eBangerState GetStateName() override;

private:
	float _timeAttack;
	int _count;
};

#endif // !BANGER_ATTACK_H
