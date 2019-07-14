#ifndef HELIT_ATTACK_H
#define HELIT_ATTACK_H
#include "../HelitState.h"

class HelitAttack :public HelitState
{
public:
	HelitAttack(Helit* helit);
	~HelitAttack();
	Helit_State getState() override;
	void update(float dt) override;

private:
	float _count;
};
#endif