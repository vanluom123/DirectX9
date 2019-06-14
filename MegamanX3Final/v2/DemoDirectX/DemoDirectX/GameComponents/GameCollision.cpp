#include "GameCollision.h"
#include <iostream>
using namespace std;


BaseObject::CollisionReturn GameCollision::rectCollision(const RECT& bound1, const RECT& bound2)
{
	BaseObject::CollisionReturn result = BaseObject::CollisionReturn();

	if (!isCollision(bound1, bound2))
	{
		result.isCollision = false;
		return result;
	}

	result.isCollision = true;

	result.regionCollision.left = max(bound1.left, bound2.left);
	result.regionCollision.right = max(bound1.right, bound2.right);
	result.regionCollision.bottom = max(bound1.bottom, bound2.bottom);
	result.regionCollision.top = max(bound1.top, bound2.top);

	return result;
}

bool GameCollision::pointCollision(float x, float y, const RECT& bound)
{
	return !(x < bound.left
		|| x > bound.right
		|| y < bound.top
		|| y > bound.bottom);
}

bool GameCollision::circleCollision(const RECT& bound, int circle_x, int circle_y, int circleRadius)
{
	int px = circle_x;
	int py = circle_y;

	if (px < bound.left)
		px = bound.left;
	else if (px > bound.right)
		px = bound.right;

	if (py > bound.bottom)
		py = bound.bottom;
	else if (py < bound.top)
		py = bound.top;

	const int dx = px - circle_x;
	const int dy = py - circle_y;

	return (dx * dx + dy * dy) <= circleRadius * circleRadius;
}

bool GameCollision::intersectRect(const RECT& obj, const RECT& other)
{
	return !(obj.left >= other.right
		|| obj.right <= other.left
		|| obj.top >= other.bottom
		|| obj.bottom <= other.top);
}

GVec2 GameCollision::Distance(BaseObject* e1, BaseObject* e2, float dt)
{
	GVec2 distance;
	distance.x = (e1->getVx() - e2->getVx()) * dt;
	distance.y = (e1->getVy() - e2->getVy()) * dt;
	return distance;
}

RECT GameCollision::getBroadphase(const RECT& object, const GVec2& distance)
{
	RECT broad = object;

	if (distance.x < 0)
		broad.left = object.left + distance.x;
	else if (distance.x > 0)
		broad.right = object.right + distance.x;

	if (distance.y > 0)
		broad.bottom = object.bottom + distance.y;
	else if (distance.y < 0)
		broad.top = object.top + distance.y;

	return broad;
}

float GameCollision::sweptAABB(const RECT& obj, const RECT& other, const GVec2& distance, BaseObject::eSideCollision& sideCollision)
{
	float dxEntry, dxExit;
	float dyEntry, dyExit;

	if (distance.x > 0.0f)
	{
		dxEntry = other.left - obj.right;
		dxExit = other.right - obj.left;
	}
	else
	{
		dxEntry = other.right - obj.left;
		dxExit = other.left - obj.right;
	}

	if (distance.y > 0.0f)
	{
		dyEntry = other.top - obj.bottom;
		dyExit = other.bottom - obj.top;
	}
	else
	{
		dyEntry = other.bottom - obj.top;
		dyExit = other.top - obj.bottom;
	}

	float txEntry, txExit;
	float tyEntry, tyExit;

	if (distance.x == 0.0f)
	{
		txEntry = -std::numeric_limits<float>::infinity();
		txExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		txEntry = dxEntry / (distance.x);
		txExit = dxExit / (distance.x);
	}

	if (distance.y == 0.0f)
	{
		tyEntry = -std::numeric_limits<float>::infinity();
		tyExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		tyEntry = dyEntry / (distance.y);
		tyExit = dyExit / (distance.y);
	}

	const float entryTime = max(txEntry, tyEntry);
	const float exitTime = min(txExit, tyExit);

	if (entryTime > exitTime || (txEntry < 0.0f && tyEntry < 0.0f) || txEntry > 1.0f || tyEntry > 1.0f)
	{
		sideCollision = BaseObject::NONE;
		return 1.0f;
	}

	if (txEntry < tyEntry)
	{
		if (dyEntry < 0.0f)
		{
			sideCollision = BaseObject::TOP;
		}
		else
		{
			sideCollision = BaseObject::BOTTOM;
		}
	}
	else
	{
		if (dxEntry < 0.0f)
		{
			sideCollision = BaseObject::LEFT;
		}
		else
		{
			sideCollision = BaseObject::RIGHT;
		}
	}

	return entryTime;
}

bool GameCollision::isCollision(const RECT& bound1, const RECT& bound2)
{
	return !(bound1.left > bound2.right
		|| bound1.right < bound2.left
		|| bound1.top > bound2.bottom
		|| bound1.bottom < bound2.top);
}

BaseObject::eSideCollision GameCollision::getSideCollision(BaseObject* e1, BaseObject* e2)
{
	RECT rect1 = e1->getBound();
	RECT rect2 = e2->getBound();
	float w = (e1->getWidth() + e2->getWidth()) / 2.0f;
	float h = (e1->getHeight() + e2->getHeight()) / 2.0f;

	float dx = e1->getPosition().x - e2->getPosition().y;
	float dy = e1->getPosition().x - e2->getPosition().y;

	if (abs(int(dx)) <= w && abs(int(dy)) <= h)
	{
		// Has a collision
		float wy = w * dy;
		float hx = h * dx;

		if (wy > hx)
		{
			if (wy > -hx)
			{
				//Collision Top e1
				return BaseObject::TOP;
			}
			//Collision Right e1
			return BaseObject::RIGHT;
		}
		if (wy > -hx)
		{
			//Collision Left e1
			return BaseObject::LEFT;
		}

		//Collision Bottom e1
		return BaseObject::BOTTOM;
	}
	//Don't collide
	return BaseObject::NONE;
}

BaseObject::eSideCollision GameCollision::getSideCollision(BaseObject* e1, BaseObject::CollisionReturn data)
{
	float xCenter = data.regionCollision.left + (data.regionCollision.right - data.regionCollision.left) / 2.0f;
	float yCenter = data.regionCollision.top + (data.regionCollision.bottom - data.regionCollision.top) / 2.0f;

	GVec2 cCenter = GVec2(xCenter, yCenter);
	GVec2 eCenter;
	eCenter.x = e1->getPosition().x;
	eCenter.y = e1->getPosition().y;

	//Get centered vector between Entity and CollisionRect
	GVec2 vec = cCenter - eCenter;

	//Vector standardization
	D3DXVec2Normalize(&vec, &vec);

	/*
	- if Vector standardization has a y > 0 => Top side of Entity
	- if Vector standardization has a y < 0 => Bottom side of Entity
	- if Vector standardization has a x > 0 => Right side of Entity
	- if Vector standardization has a x < 0 => Left side of Entity
	*/

	if (vec.y < 0)
	{
		/*
		 * Top collision
		 * Get corner cosine if it is in the 70 -> 110 Top collision
		 */
		if (vec.x <= 0.35f && vec.x >= -0.35f)
		{
			return BaseObject::TOP;
		}
		if (vec.x > 0.35f && vec.x < 0.8f)
		{
			//The angle is between 35 -> 70 on the top - right side
			return BaseObject::TOP_RIGHT;
		}
		if (vec.x >= 0.8f)
		{
			return BaseObject::RIGHT;
		}
		if (vec.x < -0.35f && vec.x >= -0.8f)
		{
			//Top - Left collision
			return BaseObject::TOP_LEFT;
		}

		return BaseObject::LEFT;
	}

	/*
	* Bottom collision
	* Get corner cosine if it is in the 70 -> 110 Bottom collision
	*/
	if (vec.x <= 0.35f && vec.x >= -0.35)
	{
		return BaseObject::BOTTOM;
	}
	if (vec.x > 0.35 && vec.x < 0.8)
	{
		//The angle is between 35 -> 70 on the Bottom - right side
		return BaseObject::BOTTOM_RIGHT;
	}
	if (vec.x >= 0.8)
	{
		return BaseObject::RIGHT;
	}
	if (vec.x < -0.35f && vec.x > -0.8f)
	{
		//Bottom - Left collision
		return BaseObject::BOTTOM_LEFT;
	}

	return BaseObject::LEFT;
}
