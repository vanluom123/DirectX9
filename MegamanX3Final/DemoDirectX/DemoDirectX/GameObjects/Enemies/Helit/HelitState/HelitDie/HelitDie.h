#ifndef HELIT_DIE_H
#define HELIT_DIE_H
#include "../HelitState.h"

class HelitDie :public HelitState
{
public:
	explicit HelitDie(HelitData* helit);
	~HelitDie() = default;
	Helit::StateName getState() override;
	void update(float dt) override;

protected:
	float timeDie;
};

#endif
