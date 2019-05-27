#pragma once

#include <d3dx9.h>
#include <d3d9.h>
#include "../GameObjects/Entity/BaseObject.h"

class GameCollision
{
public:
	//Check collision Rect and Rect
	static BaseObject::CollisionReturn RectCollision(const RECT& bound1, const RECT& bound2);

	static bool IsCollision(const RECT& bound1, const RECT& bound2);

	//if Rectangle is big, it will be errored
	static BaseObject::eSideCollision SetSideCollision(BaseObject* e1, BaseObject* e2);

	//Side of collision of Entity
	static BaseObject::eSideCollision SetSideCollision(BaseObject* e1, BaseObject::CollisionReturn data);

	//Check collision between Point and Rectangle
	static bool PointCollision(float x, float y, const RECT& bound);

	//Check collision between Rectangle and Circle
	static bool CircleCollision(const RECT& bound, int circle_x, int circle_y, int circleRadius);

	//Checking intersectRect
	static bool IntersectRect(const RECT& obj, const RECT& other);

	static GVec2 Distance(BaseObject* e1, BaseObject* e2, float dt);

	static RECT GetBroad(const RECT& object, const GVec2& distance);

	//Axis-Aligned Bounding box collision
	static float SweptAABB(const RECT& obj, const RECT& other, const GVec2& distance, BaseObject::eSideCollision& sideCollision);
};