#ifndef HELIT_STATE_H
#define HELIT_STATE_H
#include "../Helit.h"

class HelitState
{
public:
	HelitState(Helit* helit);
	virtual ~HelitState() = default;

	virtual void update(float dt);
	virtual Helit_State getState();

protected:
	Helit* m_pHelit;
	float _timeAttack;
	float _accelerateY;
};

#endif // !HELIT_STATE_H
