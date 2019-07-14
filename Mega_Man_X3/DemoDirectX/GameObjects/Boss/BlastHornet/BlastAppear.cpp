#include "BlastAppear.h"
#include "BlastIdle.h"


BlastAppear::BlastAppear(BlastHornet* b)
	: BlastHornetState(b)
{
	m_timeAppear = 0.0f;
	b->setVx(0.0f);
	b->setVy(0.0f);
}

void BlastAppear::update(float dt)
{
	m_timeAppear += dt;

	if (m_timeAppear > 1.8f)
	{
		m_timeAppear = 0.0f;
		b->setState(new BlastIdle(b));
	}
}

Enumerator::Hornet_State BlastAppear::getState()
{
	return eHornet_Appear;
}
