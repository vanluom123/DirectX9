#include "BlastShoot.h"
#include "BlastStand.h"

BlastShoot::BlastShoot(BlastData* b) :BlastState(b)
{
	_data->blast->setVx(0.0f);
	_data->blast->setVy(0.0f);
	_timeShoot = 0.0f;
	_count = -1;
}

BlastShoot::~BlastShoot()
{
	// Do nothing
}

void BlastShoot::update(float dt)
{
	_timeShoot += dt;

	if(_timeShoot > 1.0f)
	{
		_timeShoot = 0.0f;
		shoot();
	}
}

eBlastState BlastShoot::getState()
{
	return eBlastState::BLAST_STATE_SHOOT;
}

void BlastShoot::shoot()
{
	_count++;

	if (_count > 3)
	{
		_data->blast->setState(new BlastStand(_data));
		return;
	}

	if (_data->blast->getListBullet()->size() < 5)
	{
		auto ebullet = new BlastBullet();
		_data->blast->getListBullet()->push_back(ebullet);
	}

	float px = 0.0f;
	float py = _data->blast->getBound().top;

	if (_count < 4)
	{
		if (_count == 0) py += 5;
		else if (_count == 1) py += 10;
		else if (_count == 2) py += 15;
		else py += 20;

		if (_data->blast->getReverse())
			px = _data->blast->getBound().right;
		else
			px = _data->blast->getBound().left;
	}

	_data->blast->getListBullet()->at(_count)->setPosition(px, py);
	_data->blast->getListBullet()->at(_count)->setReverse(_data->blast->getReverse());
	_data->blast->getListBullet()->at(_count)->newObject();
}
