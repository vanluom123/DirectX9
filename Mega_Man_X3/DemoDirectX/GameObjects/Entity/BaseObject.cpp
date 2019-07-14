#include "BaseObject.h"

BaseObject::BaseObject()
{
	_objectType = eOject_None;
	_vx = 0;
	_vy = 0;
	_collision_time_min_x = 1.0f;
	_collision_time_min_y = 1.0f;
	_side_x = eSide_None;
	_side_y = eSide_None;
	_isAllowDraw = true;
	_isDie = false;
	_HP = 0;
	_Damage = 0;
}

BaseObject::~BaseObject()
{
	delete _entity_x;
	delete _entity_y;

	for (auto& bullet : _listBullet)
		delete bullet;
	if (!_listBullet.empty())
		_listBullet.clear();
}

RECT BaseObject::getBound()
{
	RECT bound;
	bound.left = _posX - _width / 2;
	bound.top = _posY - _height / 2;
	bound.right = _posX + _width / 2;
	bound.bottom = _posY + _height / 2;
	return bound;
}

GVec3 BaseObject::getPosition() const
{
	return { _posX, _posY, 0.0f };
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
	this->_posX = pos.x;
	this->_posY = pos.y;
	onSetPosition(pos);
}

GVec3 BaseObject::getPositionStart() const
{
	return { this->_startx, this->_starty, 0 };
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
	this->_startx = pos.x;
	this->_starty = pos.y;
	onSetPosition(pos);
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
	setPosition(this->getPosition() + pos);
}

void BaseObject::setWidth(int width)
{
	this->_width = width;
}

int BaseObject::getWidth() const
{
	return this->_width;
}

void BaseObject::setHeight(int height)
{
	this->_height = height;
}

int BaseObject::getHeight() const
{
	return this->_height;
}

void BaseObject::setHP(int hp)
{
	this->_HP = hp;
}

int BaseObject::getHP() const
{
	return this->_HP;
}

void BaseObject::setMaxHP(int hp)
{
	this->_MaxHP = hp;
}

int BaseObject::getMaxHP() const
{
	return this->_MaxHP;
}

void BaseObject::setDamage(int dame)
{
	this->_Damage = dame;
}

int BaseObject::getDamage() const
{
	return this->_Damage;
}

float BaseObject::getVx() const
{
	return this->_vx;
}

void BaseObject::setVx(float vx)
{
	this->_vx = vx;
}

void BaseObject::addVx(float vx)
{
	this->_vx += vx;
}

float BaseObject::getVy() const
{
	return this->_vy;
}

void BaseObject::setVy(float vy)
{
	this->_vy = vy;
}

void BaseObject::addVy(float vy)
{
	this->_vy += vy;
}

void BaseObject::setDraw(bool isDraw)
{
	this->_isAllowDraw = isDraw;
}

bool BaseObject::getDraw() const
{
	return this->_isAllowDraw;
}

void BaseObject::setObjectType(Object_Type objectType)
{
	this->_objectType = objectType;
}

Object_Type BaseObject::getObjectType() const
{
	return this->_objectType;
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

void BaseObject::setDie(bool die)
{
	_isDie = die;
}

bool BaseObject::getDie() const
{
	return _isDie;
}

vector<BaseObject*>* BaseObject::getListBullet()
{
	return &_listBullet;
}

void BaseObject::setId(int id)
{
	_id = id;
}

int BaseObject::getId() const
{
	return _id;
}

void BaseObject::onSetPosition(GVec3 pos)
{
}

void BaseObject::onCollision(Side_Collision side)
{
	_vx = 0.0f;
	_vy = 0.0f;
}

void BaseObject::onCollision(BaseObject* obj)
{
}

void BaseObject::onNoCollisionWithBottom()
{
}

void BaseObject::update(float dt)
{
	if (_HP > _MaxHP)
		_HP = _MaxHP;

	if (_side_x != eSide_None)
	{
		if (_collision_time_min_y == 0.0f)
		{
			if (getBound().bottom <= _entity_x->getBound().top || getBound().top >= _entity_x->getBound().bottom)
			{
				_collision_time_min_x = 1.0f;
				_side_x = eSide_None;
			}
		}
		onCollision(_side_x);
	}
	if (_side_y != eSide_None)
	{
		if (_collision_time_min_x == 0.0f)
		{
			if (getBound().right <= _entity_y->getBound().left || getBound().left >= _entity_y->getBound().right)
			{
				_collision_time_min_y = 1.0f;
				_side_y = eSide_None;
			}
		}
		onCollision(_side_y);
	}

	_posX += _vx * dt * _collision_time_min_x;
	_collision_time_min_x = 1.0f;
	_side_x = eSide_None;

	_posY += _vy * dt * _collision_time_min_y;
	_collision_time_min_y = 1.0f;
	_side_y = eSide_None;
}

void BaseObject::draw(Camera* camera, RECT rect, GVec2 scale, float angle, GVec2 rotationCenter, D3DCOLOR color)
{
}

void BaseObject::newObject()
{
}

void BaseObject::checkTimeCollision(float collisionTime, Side_Collision side, BaseObject* other)
{
	switch (side)
	{
		case eSide_Left:
		case eSide_Right:
		{
			if (collisionTime >= _collision_time_min_x)
				return;
			_collision_time_min_x = collisionTime;
			_side_x = side;
			_entity_x = other;
		}
		break;

		case eSide_Top:
		case eSide_Bottom:
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