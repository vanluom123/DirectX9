#include "BaseObject.h"

BaseObject::BaseObject()
{
	_objectType = TAG_NONE;
	_vx = 0;
	_vy = 0;
	_collision_time_min_x = 1.0f;
	_collision_time_min_y = 1.0f;
	_side_x = NONE;
	_side_y = NONE;
	_isAllowDraw = true;
	_isDie = false;
	_HP = 0;
	_Damage = 0;
}

RECT BaseObject::getBound()
{
	RECT bound;

	bound.left = _posX - _width / 2.0f;
	bound.right = _posX + _width / 2.0f;
	bound.top = _posY - _height / 2.0f;
	bound.bottom = _posY + _height / 2.0f;

	return bound;
}

void BaseObject::onCollision(eSideCollision side)
{
	_vx = 0.0f;
	_vy = 0.0f;
}

void BaseObject::update(float dt)
{
	if (_HP > _MaxHP)
		_HP = _MaxHP;

	if (_side_x != NONE)
	{
		if (_collision_time_min_y == 0.0f)
		{
			if (getBound().bottom <= _entity_x->getBound().top || getBound().top >= _entity_x->getBound().bottom)
			{
				_collision_time_min_x = 1.0f;
				_side_x = NONE;
			}
		}
		onCollision(_side_x);
	}
	if (_side_y != NONE)
	{
		if (_collision_time_min_x == 0.0f)
		{
			if (getBound().right <= _entity_y->getBound().left || getBound().left >= _entity_y->getBound().right)
			{
				_collision_time_min_y = 1.0f;
				_side_y = NONE;
			}
		}
		onCollision(_side_y);
	}

	_posX += _vx * dt * _collision_time_min_x;
	_collision_time_min_x = 1.0f;
	_side_x = NONE;

	_posY += _vy * dt * _collision_time_min_y;
	_collision_time_min_y = 1.0f;
	_side_y = NONE;
}

void BaseObject::checkTimeCollision(float collisionTime, eSideCollision side, BaseObject* other)
{
	switch (side)
	{
	case LEFT:
	case RIGHT:
	{
		if (collisionTime >= _collision_time_min_x)
			return;
		_collision_time_min_x = collisionTime;
		_side_x = side;
		_entity_x = other;
	}
	break;

	case TOP:
	case BOTTOM:
	{
		if (collisionTime >= _collision_time_min_y)
			return;
		_collision_time_min_y = collisionTime;
		_side_y = side;
		_entity_y = other;
	}
	break;

	default: break;
	}
}