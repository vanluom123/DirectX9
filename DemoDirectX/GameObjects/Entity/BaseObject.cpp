#include "BaseObject.h"
#include "../../GameDefines/GameDefine.h"
#include "../../GameComponents/GameCollision.h"

BaseObject::BaseObject()
{
	_objectType = Object_Type::NONE;
	_velocity.x = 0;
	_velocity.y = 0;

	_colTimeMinX = 1;
	_colTimeMinY = 1;
	_side_x = Side_Collision::NONE;
	_side_y = Side_Collision::NONE;

	_isAllowDraw = true;
	_isDestroy = false;
	_HP = 0;
	_Damage = 0;

	_MaxHP = 5;

	_entity_x = nullptr;
	_entity_y = nullptr;

	_height = 0;
	_width = 0;

	_id = 0;

	_isReverse = false;

	_startPosition.x = 0;
	_startPosition.y = 0;

	_position.x = _startPosition.x;
	_position.y = _startPosition.y;
}

BaseObject::~BaseObject()
{
	for (auto bullet : _listBullet)
		delete bullet;

	_listBullet.clear();
}

RECT BaseObject::getBound()
{
	RECT bound;
	bound.left = _position.x - _width / 2;
	bound.top = _position.y - _height / 2;
	bound.right = bound.left + _width;
	bound.bottom = bound.top + _height;
	return bound;
}

GVec3 BaseObject::getPosition() const
{
	return {_position.x, _position.y, 0.0f};
}

void BaseObject::setPosition(float x, float y)
{
	setPosition(GVec2(x, y));
}

void BaseObject::setPosition(GVec2 pos)
{
	setPosition(GVec3(pos.x, pos.y, 0.0f));
}

void BaseObject::setPosition(GVec3 pos)
{
	_position.x = pos.x;
	_position.y = pos.y;
}

GVec3 BaseObject::getPositionStart() const
{
	return {_startPosition.x, _startPosition.y, 0};
}

void BaseObject::setPositionStart(float x, float y)
{
	setPositionStart(GVec2(x, y));
}

void BaseObject::setPositionStart(GVec2 pos)
{
	setPositionStart(GVec3(pos.x, pos.y, 0));
}

void BaseObject::setPositionStart(GVec3 pos)
{
	_startPosition.x = pos.x;
	_startPosition.y = pos.y;
}

void BaseObject::addPosition(float x, float y)
{
	addPosition(GVec2(x, y));
}

void BaseObject::addPosition(GVec2 pos)
{
	addPosition(GVec3(pos.x, pos.y, 0));
}

void BaseObject::addPosition(GVec3 pos)
{
	setPosition(getPosition() + pos);
}

void BaseObject::setWidth(int width)
{
	_width = width;
}

int BaseObject::getWidth() const
{
	return _width;
}

void BaseObject::setHeight(int height)
{
	_height = height;
}

int BaseObject::getHeight() const
{
	return _height;
}

void BaseObject::setHP(int hp)
{
	_HP = hp;
}

int BaseObject::getHP() const
{
	return _HP;
}

void BaseObject::setMaxHP(int hp)
{
	_MaxHP = hp;
}

int BaseObject::getMaxHP() const
{
	return _MaxHP;
}

void BaseObject::setDamage(int dame)
{
	_Damage = dame;
}

int BaseObject::getDamage() const
{
	return _Damage;
}

float BaseObject::getVx() const
{
	return _velocity.x;
}

void BaseObject::setVx(float vx)
{
	_velocity.x = vx;
}

void BaseObject::addVx(float vx)
{
	_velocity.x += vx;
}

float BaseObject::getVy() const
{
	return _velocity.y;
}

void BaseObject::setVy(float vy)
{
	_velocity.y = vy;
}

void BaseObject::addVy(float vy)
{
	_velocity.y += vy;
}

void BaseObject::setDraw(bool isDraw)
{
	if (_isAllowDraw != isDraw)
		_isAllowDraw = isDraw;
}

bool BaseObject::getDraw() const
{
	return _isAllowDraw;
}

void BaseObject::setObjectType(Object_Type objectType)
{
	_objectType = objectType;
}

Object_Type BaseObject::getObjectType() const
{
	return _objectType;
}

void BaseObject::setReverse(bool reverse)
{
	if (_isReverse != reverse)
		_isReverse = reverse;
}

bool BaseObject::getReverse() const
{
	return _isReverse;
}

void BaseObject::setDestroy(bool val)
{
	if (_isDestroy != val)
		_isDestroy = val;
}

bool BaseObject::IsDestroy() const
{
	return _isDestroy;
}

vector<BaseObject*> BaseObject::getListBullet()
{
	return _listBullet;
}

void BaseObject::insertBullet(BaseObject* obj)
{
	_listBullet.push_back(obj);
}

void BaseObject::setId(int id)
{
	_id = id;
}

int BaseObject::getId() const
{
	return _id;
}

void BaseObject::onCollision(Side_Collision side)
{
	_velocity.x = 0.0f;
	_velocity.y = 0.0f;
}

void BaseObject::onCollision(BaseObject* obj)
{
	// Do nothing
}

void BaseObject::onNoCollisionWithBottom()
{
	// Do nothing
}

void BaseObject::update(float dt)
{
	if (_HP > _MaxHP)
		_HP = _MaxHP;

	if (_side_x != Side_Collision::NONE)
	{
		if (_colTimeMinY == 0.0f)
		{
			if (this->getBound().bottom <= _entity_x->getBound().top ||
				this->getBound().top >= _entity_x->getBound().bottom)
			{
				_colTimeMinX = 1.0f;
				_side_x = Side_Collision::NONE;
			}
		}
		this->onCollision(_side_x);
	}
	if (_side_y != Side_Collision::NONE)
	{
		if (_colTimeMinX == 0.0f)
		{
			if (this->getBound().right <= _entity_y->getBound().left ||
				this->getBound().left >= _entity_y->getBound().right)
			{
				_colTimeMinY = 1.0f;
				_side_y = Side_Collision::NONE;
			}
		}
		this->onCollision(_side_y);
	}

	_position.x += _velocity.x * dt * _colTimeMinX;
	_colTimeMinX = 1.0f;
	_side_x = Side_Collision::NONE;

	_position.y += _velocity.y * dt * _colTimeMinY;
	_colTimeMinY = 1.0f;
	_side_y = Side_Collision::NONE;
}

void BaseObject::checkTimeCollision(float collisionTime, Side_Collision side, BaseObject* other)
{
	switch (side)
	{
	case Side_Collision::LEFT:
	case Side_Collision::RIGHT:
		{
			if (collisionTime < _colTimeMinX)
			{
				_colTimeMinX = collisionTime;
				_side_x = side;
				_entity_x = other;
			}
			break;
		}

	case Side_Collision::TOP:
	case Side_Collision::BOTTOM:
		{
			if (collisionTime < _colTimeMinY)
			{
				_colTimeMinY = collisionTime;
				_side_y = side;
				_entity_y = other;
			}
			break;
		}

	default: break;
	}
}
