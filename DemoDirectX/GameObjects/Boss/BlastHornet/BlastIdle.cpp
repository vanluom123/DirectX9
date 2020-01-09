#include "BlastIdle.h"
#include "BlastAttack.h"

BlastIdle::BlastIdle(BlastHornet* b) : BlastHornetState(b)
{
	this->m_timeIdle = 0.0f;
	this->b->setVx(0.0f);
	this->b->setVy(0.0f);
}

void BlastIdle::update(float dt)
{
	this->m_timeIdle += dt;
	if (this->m_timeIdle > 0.25f)
	{
		this->m_timeIdle = 0.0f;
		this->b->setState(new BlastAttack(this->b));
	}
}

Enumerator::Hornet_State BlastIdle::getState()
{
	return Enumerator::Hornet_State::STAND;
}