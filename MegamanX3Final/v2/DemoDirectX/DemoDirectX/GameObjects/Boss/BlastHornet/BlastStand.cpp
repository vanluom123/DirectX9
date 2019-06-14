#include "BlastStand.h"
#include "BlastAttack.h"

BlastStand::BlastStand(BlastData* b) 
	: BlastState(b)
{
	_timeStand = 0.0f;
	_data->blast->setVx(0.0f);
	_data->blast->setVy(0.0f);
}

BlastStand::~BlastStand()
{
	// Do nothing
}

void BlastStand::update(float dt)
{
	_timeStand += dt;
	if (_timeStand > 3.0f)
	{
		_timeStand = 0.0f;
		_data->blast->setState(new BlastAttack(_data));
	}
}

eBlastState BlastStand::getState()
{
	return eBlastState::BLAST_STATE_STAND;
}
