#include "BlastDeath.h"

BlastDeath::BlastDeath(BlastHornet* b) 
	: BlastHornetState(b)
{
	this->m_timeDeath = 0.0f;
}

void BlastDeath::update(float dt)
{
	this->m_timeDeath += dt;

	if (this->m_timeDeath > 0.4f)
	{
		this->m_timeDeath = 0.0f;
		this->b->setDraw(false);
	}
}

Enumerator::Hornet_State BlastDeath::getState()
{
	return Enumerator::Hornet_State::DEATH;
}
