#ifndef HELIT_STAND_H
#define HELIT_STAND_H
#include "../HelitState.h"

class HelitStand :
	public HelitState
{
public:
	HelitStand(Helit* helit);
	~HelitStand();

	void update(float dt) override;
	virtual Helit_State getState() override;

};

#endif
