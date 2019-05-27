#ifndef HELIT_DIE_H
#define HELIT_DIE_H
#include "../HelitState.h"

class HelitDie :public HelitState
{
public:
	HelitDie(HelitData* helit);

	Helit::eHelitState GetState() override;
	void Update(float dt) override;

private:
	float m_timeDie;
};

#endif
