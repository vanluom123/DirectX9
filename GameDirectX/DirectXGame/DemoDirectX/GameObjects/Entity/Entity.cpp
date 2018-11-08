#include "Entity.h"

Entity::Entity()
{
    Tag = None;
}

RECT Entity::getBound()
{
    RECT bound;

    bound.left = _X - _Width / 2;
    bound.right = _X + _Width / 2;
    bound.top = _Y - _Height / 2;
    bound.bottom = _Y + _Height / 2;

    return bound;
}

void Entity::OnCollision(CollisionReturn data, Entity::SideCollisions side)
{
    _Vx = 0, _Vy = 0;
}

void Entity::Update(float dt)
{
    //velocity = pixel / s
    _X += _Vx * dt;
    _Y += _Vy * dt;
}

void Entity::onSetPosition(D3DXVECTOR3 pos)
{}

D3DXVECTOR3 Entity::getPosition()
{
	return { _X, _Y, 0 };
}
void Entity::setPosition(float x, float y)
{
	const auto pos = D3DXVECTOR2(x, y);
    setPosition(pos);
}
void Entity::setPosition(D3DXVECTOR2 pos)
{
	const auto position = D3DXVECTOR3(pos);
    setPosition(position);
}
void Entity::setPosition(D3DXVECTOR3 pos)
{
    this->_X = pos.x;
    this->_Y = pos.y; 
    onSetPosition(pos);
}
void Entity::addPosition(float x, float y)
{
	const auto pos = D3DXVECTOR2(x, y);
    addPosition(pos);
}
void Entity::addPosition(D3DXVECTOR2 pos)
{
	const auto position = D3DXVECTOR3(pos);
	addPosition(position);
}
void Entity::addPosition(D3DXVECTOR3 pos)
{
    this->setPosition(this->getPosition() + pos);
}

void Entity::setWidth(int width)
{
    this->_Width = width;
}
int Entity::getWidth()
{
    return _Width;
}

void Entity::setHeight(int height)
{
    this->_Height = height;
}
int Entity::getHeight()
{
    return _Height;
}

float Entity::getVx()
{
    return _Vx;
}
void Entity::setVx(float vx)
{
    this->_Vx = vx;
}
void Entity::addVx(float vx)
{
    this->_Vx += vx;
}

float Entity::getVy()
{
    return _Vy;
}
void Entity::setVy(float vy)
{
    this->_Vy = vy;
}
void Entity::addVy(float vy)
{
    this->_Vy += vy;
}