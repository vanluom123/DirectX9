#include "BlastDeath.h"

BlastDeath::BlastDeath(BlastData* b) :BlastState(b)
{
	_timeDie = 0.0f;
}

BlastDeath::~BlastDeath()
{
	// Do nothing
}

void BlastDeath::update(float dt)
{
	_timeDie += dt;
	if (_timeDie > 3.0f)
		_data->blast->setDraw(false);
}

eBlastState BlastDeath::getState()
{
	return eBlastState::BLAST_STATE_DEATH;
}
