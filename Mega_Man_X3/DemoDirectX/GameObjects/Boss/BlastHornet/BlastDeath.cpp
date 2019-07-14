#include "BlastDeath.h"

BlastDeath::BlastDeath(BlastHornet* b) 
	: BlastHornetState(b)
{
	m_timeDeath = 0.0f;
}

void BlastDeath::update(float dt)
{
	m_timeDeath += dt;

	if (m_timeDeath > 0.4f)
	{
		m_timeDeath = 0.0f;
		b->setDraw(false);
	}
}

Enumerator::Hornet_State BlastDeath::getState()
{
	return eHornet_Death;
}
