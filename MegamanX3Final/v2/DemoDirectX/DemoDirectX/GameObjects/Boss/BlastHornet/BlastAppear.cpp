#include "BlastAppear.h"
#include "BlastStand.h"


BlastAppear::BlastAppear(BlastData* b) :BlastState(b)
{
	_data->blast->setVx(0.0f);
	_data->blast->setVy(50.0f);
	_time_appear = 0.0f;
}

BlastAppear::~BlastAppear()
{
	// Do nothing
}

void BlastAppear::update(float dt)
{
	_time_appear += dt;
	if (_time_appear > 2.0f)
	{
		_data->blast->setVy(-50.0f);
	}

	if (_time_appear > 5.0f)
	{
		_time_appear = 0.0f;
		_data->blast->setState(new BlastStand(_data));
	}
}

eBlastState BlastAppear::getState()
{
	return eBlastState::BLAST_STATE_APPEAR;
}
