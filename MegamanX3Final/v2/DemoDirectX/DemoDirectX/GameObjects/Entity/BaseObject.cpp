#include "BaseObject.h"

BaseObject::BaseObject()
{
	_objectType = TAG_NONE;
	_vx = 0;
	_vy = 0;
	_collisionTimeMinX = 1.0f;
	_collisionTimeMinY = 1.0f;
	_sideX = NONE;
	_sideY = NONE;
	_isAllowDraw = true;
	_isDie = false;
	_HP = 0;
	_Damage = 0;
}

RECT BaseObject::GetBound()
{
	RECT bound;

	bound.left = _posX - _width / 2.0f;
	bound.right = _posX + _width / 2.0f;
	bound.top = _posY - _height / 2.0f;
	bound.bottom = _posY + _height / 2.0f;

	return bound;
}

void BaseObject::OnCollision(eSideCollision side)
{
	_vx = 0, _vy = 0;
}

void BaseObject::OnCollision(BaseObject* obj)
{}

void BaseObject::OnNoCollisionWithBottom()
{}

std::vector<BaseObject*>* BaseObject::GetListBullet()
{
	return &_listBullet;
}

void BaseObject::SetId(int id)
{
	_id = id;
}

int BaseObject::GetId() const
{
	return _id;
}

void BaseObject::Update(float dt)
{
	if (_HP > _MaxHP)
		_HP = _MaxHP;

	if (_sideX != NONE)
	{
		if (_collisionTimeMinY == 0.0f)
		{
			if (GetBound().bottom <= _entityX->GetBound().top || GetBound().top >= _entityX->GetBound().bottom)
			{
				_collisionTimeMinX = 1.0f;
				_sideX = NONE;
			}
		}
		OnCollision(_sideX);
	}
	if (_sideY != NONE)
	{
		if (_collisionTimeMinX == 0.0f)
		{
			if (GetBound().right <= _entityY->GetBound().left || GetBound().left >= _entityY->GetBound().right)
			{
				_collisionTimeMinY = 1.0f;
				_sideY = NONE;
			}
		}
		OnCollision(_sideY);
	}
	_posX += _vx * dt * _collisionTimeMinX;
	_collisionTimeMinX = 1.0f;
	_sideX = NONE;

	_posY += _vy * dt * _collisionTimeMinY;
	_collisionTimeMinY = 1.0f;
	_sideY = NONE;
}

void BaseObject::CheckTimeCollision(float collisionTime, eSideCollision side, BaseObject* other)
{
	switch (side)
	{
	case LEFT:
	case RIGHT:
		if (collisionTime >= _collisionTimeMinX)
			return;
		_collisionTimeMinX = collisionTime;
		_sideX = side;
		_entityX = other;
		break;


	case TOP:
	case BOTTOM:
		if (collisionTime >= _collisionTimeMinY)
			return;
		_collisionTimeMinY = collisionTime;
		_sideY = side;
		_entityY = other;
		break;


	default: break;
	}
}