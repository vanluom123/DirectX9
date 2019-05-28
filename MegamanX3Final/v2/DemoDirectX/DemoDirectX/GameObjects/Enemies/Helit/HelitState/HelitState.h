#ifndef HELIT_STATE_H
#define HELIT_STATE_H
#include "../Helit.h"

class HelitState
{
public:
	HelitState(HelitData* helit);
	virtual Helit::eHelitState GetState() = 0;
	virtual void Update(float dt);

protected:
	HelitData* _pHelitData;
	float _timeAttack;
	float _accelerateY;
};

#endif // !HELIT_STATE_H
