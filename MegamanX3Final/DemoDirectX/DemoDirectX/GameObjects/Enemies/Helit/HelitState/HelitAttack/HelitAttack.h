#ifndef HELIT_ATTACK_H
#define HELIT_ATTACK_H
#include "../HelitState.h"

class HelitAttack :public HelitState
{
public:
	explicit HelitAttack(HelitData* helit);
	~HelitAttack() = default;
	Helit::StateName getState() override;
	void update(float dt) override;

private:
	float count;
};
#endif