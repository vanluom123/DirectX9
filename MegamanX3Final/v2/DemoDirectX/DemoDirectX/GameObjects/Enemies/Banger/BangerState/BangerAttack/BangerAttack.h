#ifndef BANGER_ATTACK_H
#define BANGER_ATTACK_H
#include "../BangerState.h"

class BangerAttack :
	public BangerState
{
public:
	 BangerAttack(Banger* banger);
	 ~BangerAttack();
	void Update(float dt) override;
	virtual Banger_State getState() override;

private:
	float _timeAttack;
	int _count;
};

#endif // !BANGER_ATTACK_H
