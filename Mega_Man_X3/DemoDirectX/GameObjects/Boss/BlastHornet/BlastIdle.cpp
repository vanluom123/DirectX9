#include "BlastIdle.h"
#include "BlastAttack.h"

BlastIdle::BlastIdle(BlastHornet* b) : BlastHornetState(b)
{
	m_timeIdle = 0.0f;
	b->setVx(0.0f);
	b->setVy(0.0f);
}

void BlastIdle::update(float dt)
{
	m_timeIdle += dt;
	if (m_timeIdle > 0.25f)
	{
		m_timeIdle = 0.0f;
		b->setState(new BlastAttack(b));
	}
}

Enumerator::Hornet_State BlastIdle::getState()
{
	return eHornet_Idle;
}