#pragma once

#include <d3dx9.h>
#include <d3d9.h>
#include "../GameObjects/Entity/BaseObject.h"

class GameCollision
{
public:
	//Check collision Rect and Rect
	static BaseObject::CollisionReturn rectCollision(RECT rect1, RECT rect2);

	static bool IsCollision(RECT rect1, RECT rect2);

	//if Rectangle is big, it will be errored
	static BaseObject::eSideCollision getSideCollision(BaseObject* e1, BaseObject* e2);

	//Side of collision of Entity
	static BaseObject::eSideCollision getSideCollision(BaseObject* e1, BaseObject::CollisionReturn data);

	//Check collision between Point and Rectangle
	static bool pointCollision(float x, float y, RECT rect);

	//Check collision between Rectangle and Circle
	static bool circleCollision(RECT rect, int circle_x, int circle_y, int circleRadius);

	//Checking intersectRect
	static bool intersectRect(RECT obj, RECT other);

	static GVec2 Distance(BaseObject* e1, BaseObject* e2, float dt);

	static RECT getBroad(RECT object, GVec2 distance);

	//Axis-Aligned Bounding box collision
	static float SweptAABB(RECT obj, RECT other, GVec2 distance, BaseObject::eSideCollision& sideCollision);
};
