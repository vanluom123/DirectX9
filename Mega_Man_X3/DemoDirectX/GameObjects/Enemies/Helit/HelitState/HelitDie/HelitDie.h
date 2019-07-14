#ifndef HELIT_DIE_H
#define HELIT_DIE_H
#include "../HelitState.h"

class HelitDie :public HelitState
{
public:
	HelitDie(Helit* helit);
	~HelitDie();
	Helit_State getState() override;
	void update(float dt) override;

private:
	float _timeDie;
};

#endif
