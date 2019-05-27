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
	float m_timeAttack;
	int m_count;
};

#endif // !BANGER_ATTACK_H
