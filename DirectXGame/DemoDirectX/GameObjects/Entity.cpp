#include "Entity.h"
#include "../GameComponents/GameCollision.h"

Entity::~Entity()
{}

Entity::Entity()
{
    Tag = None;
}

RECT Entity::GetBound()
{
    RECT bound;

    bound.left = posX - width / 2;
    bound.right = posX + width / 2;
    bound.top = posY - height / 2;
    bound.bottom = posY + height / 2;

    return bound;
}

D3DXVECTOR3 Entity::GetPosition()
{
	return { posX, posY, 0 };
}

void Entity::OnCollision(CollisionReturn data, Entity::SideCollisions side)
{
    vx = 0, vy = 0;
}

void Entity::OnSetPosition(D3DXVECTOR3 pos)
{}

void Entity::Update(float dt)
{

    //velocity = pixel / s
    posX += vx * dt;
    posY += vy * dt;
}

void Entity::SetPosition(float x, float y)
{
	D3DXVECTOR2 pos = D3DXVECTOR2(x, y);
    SetPosition(pos);
}

void Entity::SetPosition(D3DXVECTOR2 pos)
{
	D3DXVECTOR3 position = D3DXVECTOR3(pos);
    SetPosition(position);
}

void Entity::SetPosition(D3DXVECTOR3 pos)
{
    this->posX = pos.x;
    this->posY = pos.y; 
    OnSetPosition(pos);
}

void Entity::AddPosition(float x, float y)
{
	D3DXVECTOR2 pos = D3DXVECTOR2(x, y);
    AddPosition(pos);
}

void Entity::AddPosition(D3DXVECTOR2 pos)
{
	D3DXVECTOR3 position = D3DXVECTOR3(pos);
	AddPosition(position);
}

void Entity::AddPosition(D3DXVECTOR3 pos)
{
    this->SetPosition(this->GetPosition() + pos);
}

void Entity::SetWidth(int width)
{
    this->width = width;
}

int Entity::GetWidth()
{
    return width;
}

void Entity::SetHeight(int height)
{
    this->height = height;
}

int Entity::GetHeight()
{
    return height;
}

float Entity::GetVx()
{
    return vx;
}

void Entity::SetVx(float vx)
{
    this->vx = vx;
}

void Entity::AddVx(float vx)
{
    this->vx += vx;
}

float Entity::GetVy()
{
    return vy;
}

void Entity::SetVy(float vy)
{
    this->vy = vy;
}

void Entity::AddVy(float vy)
{
    this->vy += vy;
}