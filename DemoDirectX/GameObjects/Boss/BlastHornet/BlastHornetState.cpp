#include "BlastHornetState.h"

BlastHornetState::BlastHornetState(BlastHornet* b): b(b)
{
	this->m_transX = 0.0f;
	this->m_transY = 0.0f;
	this->m_confirmMoveUp = false;
}

BlastHornetState::~BlastHornetState()
{}

void BlastHornetState::update(float dt)
{}

void BlastHornetState::onCollision(Side_Collision side)
{}

Hornet_State BlastHornetState::getState()
{
	return Enumerator::Hornet_State::NONE;
}

bool BlastHornetState::getConfirmMoveUp() const
{
	return this->m_confirmMoveUp;
}
