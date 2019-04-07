#pragma once

#include <d3dx9.h>
#include <d3d9.h>
#include "../GameObjects/Entity/Entity.h"

class GameCollision
{
public:
	//Check collision Rect and Rect
	static Entity::CollisionReturn rectCollision(RECT rect1, RECT rect2);

	static bool IsCollision(RECT rect1, RECT rect2);

	//if Rectangle is big, it will be errored
	static Entity::SideCollisions getSideCollision(Entity* e1, Entity* e2);

	//Side of collision of Entity
	static Entity::SideCollisions getSideCollision(Entity* e1, Entity::CollisionReturn data);

	//Check collision between Point and Rectangle
	static bool pointCollision(float x, float y, RECT rect);

	//Check collision between Rectangle and Circle
	static bool circleCollision(RECT rect, int circle_x, int circle_y, int circleRadius);

	//Checking intersectRect
	static bool intersectRect(RECT obj, RECT other);

	static D3DXVECTOR2 Distance(Entity* e1, Entity* e2, float dt);

	static RECT getBroad(RECT object, D3DXVECTOR2 distance);

	//Axis-Aligned Bounding box collision
	static float SweptAABB(RECT obj, RECT other, D3DXVECTOR2 distance, Entity::SideCollisions& sideCollision);
};
