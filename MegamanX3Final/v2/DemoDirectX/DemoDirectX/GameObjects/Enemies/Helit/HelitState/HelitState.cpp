#include "HelitState.h"

HelitState::HelitState(Helit* helit)
{
	m_pHelit = helit;
}

void HelitState::update(float dt)
{
}

Helit_State HelitState::getState()
{
	return eHelit_None;
}
