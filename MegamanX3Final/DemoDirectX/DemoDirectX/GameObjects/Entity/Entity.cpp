#include "Entity.h"

Entity::Entity()
{
	tag = TAG_NONE;
	vx = 0, vy = 0;
	collisionTimeMinX = 1.0f;
	collisionTimeMinY = 1.0f;
	sideX = NONE;
	sideY = NONE;
	allowDraw = true;
	isDie = false;
	HP = 0, Damage = 0;
}

RECT Entity::GetBound()
{
	RECT bound;

	bound.left = x - width / 2.0f;
	bound.right = x + width / 2.0f;
	bound.top = y - height / 2.0f;
	bound.bottom = y + height / 2.0f;

	return bound;
}

void Entity::OnCollision(SideCollisions side)
{
	vx = 0, vy = 0;
}

void Entity::OnCollision(Entity* obj)
{}

void Entity::OnNoCollisionWithBottom()
{}

std::vector<Entity*>* Entity::GetListBullet()
{
	return &listBullet;
}

void Entity::Update(float dt)
{
	if (HP > MaxHP)
		HP = MaxHP;

	if (sideX != NONE)
	{
		if (collisionTimeMinY == 0.0f)
		{
			if (GetBound().bottom <= entityX->GetBound().top || GetBound().top >= entityX->GetBound().bottom)
			{
				collisionTimeMinX = 1.0f;
				sideX = NONE;
			}
		}
		OnCollision(sideX);
	}
	if (sideY != NONE)
	{
		if (collisionTimeMinX == 0.0f)
		{
			if (GetBound().right <= entityY->GetBound().left || GetBound().left >= entityY->GetBound().right)
			{
				collisionTimeMinY = 1.0f;
				sideY = NONE;
			}
		}
		OnCollision(sideY);
	}
	x += vx * dt * collisionTimeMinX;
	collisionTimeMinX = 1.0f;
	sideX = NONE;

	y += vy * dt * collisionTimeMinY;
	collisionTimeMinY = 1.0f;
	sideY = NONE;
}

void Entity::CheckTimeCollision(float collisionTime, SideCollisions side, Entity* other)
{
	switch (side)
	{
	case LEFT:
	case RIGHT:
		if (collisionTime >= collisionTimeMinX)
			return;
		collisionTimeMinX = collisionTime;
		sideX = side;
		entityX = other;
		break;


	case TOP:
	case BOTTOM:
		if (collisionTime >= collisionTimeMinY)
			return;
		collisionTimeMinY = collisionTime;
		sideY = side;
		entityY = other;
		break;


	default: break;
	}
}