#include "Entity.h"

Entity::Entity()
{
    Tag = None;
}

RECT Entity::GetBound()
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

void Entity::_OnSetPosition(D3DXVECTOR3 pos)
{}

D3DXVECTOR3 Entity::GetPosition()
{
	return { _X, _Y, 0 };
}
void Entity::SetPosition(float x, float y)
{
	const auto pos = D3DXVECTOR2(x, y);
    SetPosition(pos);
}
void Entity::SetPosition(D3DXVECTOR2 pos)
{
	const auto position = D3DXVECTOR3(pos);
    SetPosition(position);
}
void Entity::SetPosition(D3DXVECTOR3 pos)
{
    this->_X = pos.x;
    this->_Y = pos.y; 
    _OnSetPosition(pos);
}
void Entity::AddPosition(float x, float y)
{
	const auto pos = D3DXVECTOR2(x, y);
    AddPosition(pos);
}
void Entity::AddPosition(D3DXVECTOR2 pos)
{
	const auto position = D3DXVECTOR3(pos);
	AddPosition(position);
}
void Entity::AddPosition(D3DXVECTOR3 pos)
{
    this->SetPosition(this->GetPosition() + pos);
}

void Entity::SetWidth(int width)
{
    this->_Width = width;
}
int Entity::GetWidth()
{
    return _Width;
}

void Entity::SetHeight(int height)
{
    this->_Height = height;
}
int Entity::GetHeight()
{
    return _Height;
}

float Entity::GetVx()
{
    return _Vx;
}
void Entity::SetVx(float vx)
{
    this->_Vx = vx;
}
void Entity::AddVx(float vx)
{
    this->_Vx += vx;
}

float Entity::GetVy()
{
    return _Vy;
}
void Entity::SetVy(float vy)
{
    this->_Vy = vy;
}
void Entity::AddVy(float vy)
{
    this->_Vy += vy;
}