#include "Entity.h"

Entity::Entity()
{}

Entity::~Entity()
{}

RECT Entity::GetBound()
{
	RECT rect;
	rect.left = long(posX - float(mWidth) / 2);
	rect.right = rect.left + mWidth; // rect.right = posX + mWidth / 2;
	rect.top = long(posY - float(mHeight) / 2);
	rect.bottom = rect.top + mHeight; // rect.bottom = posY + mHeight / 2;

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
	return mWidth;
}

void Entity::SetWidth(int width)
{
	this->mWidth = width;
}

int Entity::GetHeight()
{
	return mHeight;
}

void Entity::SetHeight(int height)
{
	this->mHeight = height;
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
	this->posX += this->vx*dt; // De cho vi tri di chuyen chi viec cong them cho dt. Mat khac o day co van toc nen vtri se cong voi van toc * dt 
	this->posY += this->vy*dt;
}

void Entity::OnSetPosition(D3DXVECTOR3 pos)
{
}
