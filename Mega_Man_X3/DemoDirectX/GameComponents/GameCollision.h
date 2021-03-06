#pragma once

#include <d3dx9.h>
#include <d3d9.h>
#include "../GameObjects/Entity/BaseObject.h"

class GameCollision
{
public:
	//Check collision Rect and Rect
	static BaseObject::CollisionReturn rectCollision(const RECT& bound1, const RECT& bound2);

	static bool isCollision(const RECT& bound1, const RECT& bound2);

	//if Rectangle is big, it will be errored
	static Side_Collision getSideCollision(BaseObject* e1, BaseObject* e2);

	//Side of collision of Entity
	static Side_Collision getSideCollision(BaseObject* e1, BaseObject::CollisionReturn data);

	//Check collision between Point and Rectangle
	static bool pointCollision(float x, float y, const RECT& bound);

	//Check collision between Rectangle and Circle
	static bool circleCollision(const RECT& bound, int circle_x, int circle_y, int circleRadius);

	//Checking intersectRect
	static bool intersectRect(const RECT& obj, const RECT& other);

	static GVec2 Distance(BaseObject* e1, BaseObject* e2, float dt);

	static RECT getBroadphase(const RECT& object, const GVec2& distance);

	//Axis-Aligned Bounding box collision
	static float sweptAABB(const RECT& obj, const RECT& other, const GVec2& distance, Side_Collision& sideCollision);
};