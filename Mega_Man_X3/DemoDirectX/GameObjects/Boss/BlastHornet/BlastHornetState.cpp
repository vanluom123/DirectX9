#include "BlastHornetState.h"

BlastHornetState::BlastHornetState(BlastHornet* b): b(b)
{
	m_transX = 0.0f;
	m_transY = 0.0f;
	m_confirmMoveUp = false;
}

BlastHornetState::~BlastHornetState()
{}

void BlastHornetState::update(float dt)
{}

void BlastHornetState::onCollision(Side_Collision side)
{}

Hornet_State BlastHornetState::getState()
{
	return eHornet_None;
}

bool BlastHornetState::getConfirmMoveUp() const
{
	return m_confirmMoveUp;
}
