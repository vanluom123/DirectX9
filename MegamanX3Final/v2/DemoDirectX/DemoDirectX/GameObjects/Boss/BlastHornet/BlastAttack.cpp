#include "BlastAttack.h"
#include "BlastStand.h"

BlastAttack::BlastAttack(BlastData* b) :BlastState(b)
{
	_data->blast->setVx(0.0f);
	_data->blast->setVy(0.0f);
	_speedX = 50.0f;
	_speedY = 50.0f;
	_attackType = MOVE_DOWN;
}

BlastAttack::~BlastAttack()
{
	// Do nothing
}

void BlastAttack::update(float dt)
{
	switch (_attackType)
	{
	case BlastAttack::MOVE_UP:
	{
		// vy = vx - 300.0f
		float vy = 0.0f;
		vy = _data->blast->getVx() - 300.0f;

		_data->blast->setVy(vy);
		_data->blast->addVx(_speedX);

		if (_data->blast->getVx() > 300.0f)
			_data->blast->setVx(300.0f);
	}
	break;

	case BlastAttack::MOVE_DOWN:
	{
		// vx = -vy + 300.0f
		// x += vx * dt * collision_time_min_x
		// y += vy * dt * collision_time_min_y

		float vx = 0.0f;
		vx = -_data->blast->getVy() + 300.0f;

		_data->blast->setVx(vx);
		_data->blast->addVy(_speedY);

		if (_data->blast->getVy() > 300.0f)
			_data->blast->setVy(300.0f);
	}
	break;

	default:
		break;
	}
}

void BlastAttack::onCollision(BaseObject::eSideCollision side)
{
	if (side == BaseObject::BOTTOM)
		_attackType = MOVE_UP;
	if (side == BaseObject::TOP)
	{
		_attackType = DONT_MOVE;
		_data->blast->setState(new BlastStand(_data));
	}
}

eBlastState BlastAttack::getState()
{
	return eBlastState::BLAST_STATE_ATTACK;
}
