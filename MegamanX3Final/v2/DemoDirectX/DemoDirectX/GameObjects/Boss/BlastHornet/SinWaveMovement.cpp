#include "SinWaveMovement.h"

SinWaveMovement::SinWaveMovement(BlastData* b) : BlastState(b)
{
	_count = -1;
	_timeMove = 0.0f;
}

SinWaveMovement::~SinWaveMovement()
{
	// Do nothing
}

void SinWaveMovement::update(float dt)
{
	double pos_x = _data->blast->getPosition().x + newPosY(1, 1, GetTickCount());
	double pos_y = _data->blast->getPosition().y + newPosX(GetTickCount(), 300.0f);
	_data->blast->setPosition(float(pos_x), float(pos_y));
}

eBlastState SinWaveMovement::getState()
{
	return eBlastState();
}

void SinWaveMovement::shoot()
{
	_count++;

	if (_count > 3)
	{
		_count = -1;
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

	_data->blast->getListBullet()->at(_count)->newObject();
}

void SinWaveMovement::GPS()
{
}

void SinWaveMovement::MoveRight()
{
}

void SinWaveMovement::MoveLeft()
{
}

double SinWaveMovement::newPosY(int amplitude, int frequency, int milliSecs)
{
	return amplitude * sin(2 * 3.14 * frequency * (milliSecs / 1000));
}

double SinWaveMovement::newPosX(int milliSecs, int speed)
{
	return double(milliSecs / 1000) * speed;
}
