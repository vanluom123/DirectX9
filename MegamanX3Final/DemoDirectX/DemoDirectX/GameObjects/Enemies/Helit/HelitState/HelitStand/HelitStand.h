#ifndef HELIT_STAND_H
#define HELIT_STAND_H
#include "../HelitState.h"

class HelitStand :public HelitState
{
public:
	explicit HelitStand(HelitData* helit);
	~HelitStand() = default;
	Helit::StateName getState() override;
	void update(float dt) override;
};

#endif
