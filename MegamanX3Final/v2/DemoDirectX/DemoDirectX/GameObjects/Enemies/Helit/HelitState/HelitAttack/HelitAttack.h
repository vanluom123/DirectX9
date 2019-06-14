#ifndef HELIT_ATTACK_H
#define HELIT_ATTACK_H
#include "../HelitState.h"

class HelitAttack :public HelitState
{
public:
	HelitAttack(HelitData* helit);

	Helit::eHelitState getState() override;
	void update(float dt) override;

private:
	float _count;
};
#endif