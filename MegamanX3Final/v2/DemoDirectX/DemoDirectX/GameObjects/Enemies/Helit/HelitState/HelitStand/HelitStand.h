#ifndef HELIT_STAND_H
#define HELIT_STAND_H
#include "../HelitState.h"

class HelitStand :public HelitState
{
public:
	HelitStand(HelitData* helit);

	Helit::eHelitState getState() override;
	void update(float dt) override;
};

#endif
