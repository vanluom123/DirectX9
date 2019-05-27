#ifndef HELIT_ATTACK_H
#define HELIT_ATTACK_H
#include "../HelitState.h"

class HelitAttack :public HelitState
{
public:
	HelitAttack(HelitData* helit);

	Helit::eHelitState GetState() override;
	void Update(float dt) override;

private:
	float m_count;
};
#endif