#include "Entity.h"

Entity::Entity()
{
	Tag = None;
}

Entity::~Entity()
{}

RECT Entity::GetBound()
{
	RECT rect;

	rect.left = posX - width / 2;
	rect.right = rect.left + width;
	rect.top = posY + height / 2;
	rect.bottom = rect.top - height;

	return rect;
}

D3DXVECTOR3 Entity::GetPosition()
{
	return { posX, posY, 0 };
}

void Entity::SetPosition(D3DXVECTOR3 pos)
{
	this->posX = pos.x;
	this->posY = pos.y;

	OnSetPosition(pos);
}

void Entity::SetPosition(float x, float y)
{
	this->SetPosition(D3DXVECTOR3(x, y, 0));
}

void Entity::SetPosition(D3DXVECTOR2 pos)
{
	this->SetPosition(D3DXVECTOR3(pos.x, pos.y, 0));
}

void Entity::AddPosition(D3DXVECTOR3 pos)
{
	this->SetPosition(this->GetPosition() + pos);
}

void Entity::AddPosition(float x, float y)
{
	this->AddPosition(D3DXVECTOR3(x, y, 0));
}

void Entity::AddPosition(D3DXVECTOR2 pos)
{
	this->AddPosition(D3DXVECTOR3(pos));
}

int Entity::GetWidth()
{
	return width;
}

void Entity::SetWidth(int width)
{
	this->width = width;
}

int Entity::GetHeight()
{
	return height;
}

void Entity::SetHeight(int height)
{
	this->height = height;
}

float Entity::GetVx()
{
	return this->vx;
}

void Entity::SetVx(float vx)
{
	this->vx = vx;
}

float Entity::GetVy()
{
	return this->vy;
}

void Entity::SetVy(float vy)
{
	this->vy = vy;
}

void Entity::AddVx(float vx)
{
	this->vx += vx;
}

void Entity::AddVy(float vy)
{
	this->vy += vy;
}

void Entity::Update(float dt)
{
	//Velocity pixel / s
	this->posX += this->vx * dt; // De cho vi tri di chuyen chi viec cong them cho dt. Mat khac o day co van toc							nen vi tri se cong voi van toc * dt 
	this->posY += this->vy * dt;
}

void Entity::OnCollision(Entity* entityCollision, CollisionReturn data, SideCollision side)
{
	vx = 0;
	vy = 0;
}

void Entity::OnSetPosition(D3DXVECTOR3 pos)
{}
