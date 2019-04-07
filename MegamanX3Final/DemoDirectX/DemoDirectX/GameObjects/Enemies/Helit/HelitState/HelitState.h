#ifndef HELIT_STATE_H
#define HELIT_STATE_H
#include "../Helit.h"

class HelitState
{
public:
	explicit HelitState(HelitData* helit);
	virtual ~HelitState() = default;
	virtual Helit::StateName getState() = 0;
	virtual void update(float dt);

protected:
	HelitData* helit;
	float timeAttack;
	float translateY;
};

#endif // !HELIT_STATE_H
